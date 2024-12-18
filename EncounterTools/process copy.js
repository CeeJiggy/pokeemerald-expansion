const fs = require('fs').promises;
const path = require('path');
const readline = require('readline');
const XLSX = require('xlsx');

// Set up logging
const logFile = 'encounter_processing.log';
function log(message, type = 'INFO') {
    const timestamp = new Date().toISOString();
    const logMessage = `${timestamp} - ${type} - ${message}`;
    console.log(logMessage);
    return fs.appendFile(logFile, logMessage + '\n');
}

async function processEncounters(jsonFile, outputFile) {
    try {
        // Check if input file exists
        try {
            await fs.access(jsonFile);
        } catch {
            throw new Error(`Input file not found: ${jsonFile}`);
        }

        // Read JSON file
        let data;
        try {
            const rawData = await fs.readFile(jsonFile, 'utf8');
            data = JSON.parse(rawData);
        } catch (e) {
            throw new Error(`Error reading/parsing JSON file: ${e.message}`);
        }

        // Validate JSON structure
        if (!data.wild_encounter_groups) {
            throw new Error("Missing 'wild_encounter_groups' in JSON data");
        }

        // Get rod groups from the first encounter group's fields
        let rodGroupDefinitions = {};
        if (data.wild_encounter_groups[0]?.fields) {
            const fishingField = data.wild_encounter_groups[0].fields.find(f => f.type === 'fishing_mons');
            if (fishingField?.groups) {
                rodGroupDefinitions = fishingField.groups;
            }
        }

        // Initialize worksheets data
        const worksheets = {
            land: [['Location', 'Encounter Rate', 'Pokemon', 'Level Range']],
            water: [['Location', 'Encounter Rate', 'Pokemon', 'Level Range']],
            rock_smash: [['Location', 'Encounter Rate', 'Pokemon', 'Level Range']],
            hidden: [['Location', 'Encounter Rate', 'Pokemon', 'Level Range']],
            fishing: [['Location', 'Rod Type', 'Encounter Rate', 'Pokemon', 'Level Range']]
        };

        let processedEncounters = 0;
        let processedLocations = new Set();

        // Process each encounter group
        for (const [groupIdx, group] of data.wild_encounter_groups.entries()) {
            console.log(`Processing encounter group ${groupIdx + 1}/${data.wild_encounter_groups.length}`);
            await log(`Processing encounter group ${groupIdx + 1}/${data.wild_encounter_groups.length}`);

            if (!group.encounters) {
                console.log(`WARNING: Group ${groupIdx + 1} has no encounters field`);
                await log(`Group ${groupIdx + 1} has no encounters field`, 'WARNING');
                continue;
            }

            for (const encounter of group.encounters) {
                try {
                    if (!encounter.map) {
                        continue;
                    }

                    const location = encounter.map.replace('MAP_', '').replace(/_/g, ' ').replace(/\w\S*/g,
                        txt => txt.charAt(0).toUpperCase() + txt.substr(1).toLowerCase());
                    processedLocations.add(location);

                    // Process standard encounter types
                    const encounterTypes = {
                        land_mons: 'land',
                        water_mons: 'water',
                        rock_smash_mons: 'rock_smash',
                        hidden_mons: 'hidden'
                    };

                    for (const [typeKey, worksheetKey] of Object.entries(encounterTypes)) {
                        if (encounter[typeKey]) {
                            try {
                                const encounterData = encounter[typeKey];
                                const encounterRate = encounterData.encounter_rate || 0;

                                if (!encounterData.mons) {
                                    console.log(`WARNING: Missing 'mons' in ${typeKey} for ${location}`);
                                    await log(`Missing 'mons' in ${typeKey} for ${location}`, 'WARNING');
                                    continue;
                                }

                                for (const mon of encounterData.mons) {
                                    try {
                                        worksheets[worksheetKey].push([
                                            location,
                                            `${encounterRate}%`,
                                            mon.species.replace('SPECIES_', '').replace(/_/g, ' '),
                                            `${mon.min_level}-${mon.max_level}`
                                        ]);
                                        processedEncounters++;
                                    } catch (e) {
                                        console.log(`ERROR: Missing key in Pokemon data: ${e.message} for ${location}`);
                                        await log(`Missing key in Pokemon data: ${e.message} for ${location}`, 'ERROR');
                                    }
                                }
                            } catch (e) {
                                console.log(`ERROR: Error processing ${typeKey} in ${location}: ${e.message}`);
                                await log(`Error processing ${typeKey} in ${location}: ${e.message}`, 'ERROR');
                            }
                        }
                    }

                    // Special handling for fishing encounters
                    if (encounter.fishing_mons) {
                        try {
                            const fishingData = encounter.fishing_mons;
                            const encounterRate = fishingData.encounter_rate || 0;

                            if (!fishingData.mons) {
                                console.log(`WARNING: Missing 'mons' in fishing_mons for ${location}`);
                                await log(`Missing 'mons' in fishing_mons for ${location}`, 'WARNING');
                                continue;
                            }

                            fishingData.mons.forEach((mon, monIdx) => {
                                try {
                                    let rodType = 'Unknown Rod';
                                    for (const [rodName, indices] of Object.entries(rodGroupDefinitions)) {
                                        if (indices.includes(monIdx)) {
                                            rodType = rodName.replace(/_/g, ' ').replace(/\w\S*/g,
                                                txt => txt.charAt(0).toUpperCase() + txt.substr(1).toLowerCase());
                                            break;
                                        }
                                    }

                                    worksheets.fishing.push([
                                        location,
                                        rodType,
                                        `${encounterRate}%`,
                                        mon.species.replace('SPECIES_', '').replace(/_/g, ' '),
                                        `${mon.min_level}-${mon.max_level}`
                                    ]);
                                    processedEncounters++;
                                } catch (e) {
                                    console.log(`ERROR: Missing key in fishing Pokemon data: ${e.message} for ${location}`);
                                    log(`Missing key in fishing Pokemon data: ${e.message} for ${location}`, 'ERROR');
                                }
                            });
                        } catch (e) {
                            console.log(`ERROR: Error processing fishing encounters in ${location}: ${e.message}`);
                            await log(`Error processing fishing encounters in ${location}: ${e.message}`, 'ERROR');
                        }
                    }
                } catch (e) {
                    console.log(`ERROR: Error processing encounter: ${e.message}`);
                    await log(`Error processing encounter: ${e.message}`, 'ERROR');
                }
            }
        }

        // Create workbook and add worksheets
        const workbook = XLSX.utils.book_new();

        for (const [sheetName, data] of Object.entries(worksheets)) {
            if (data.length > 1) { // Only create worksheet if there's data beyond headers
                // Format sheet name: capitalize first letter and replace underscores with spaces
                const formattedSheetName = sheetName
                    .split('_')
                    .map(word => word.charAt(0).toUpperCase() + word.slice(1))
                    .join(' ');
                const worksheet = XLSX.utils.aoa_to_sheet(data);
                XLSX.utils.book_append_sheet(workbook, worksheet, formattedSheetName);
            }
        }

        // Write Excel file
        XLSX.writeFile(workbook, outputFile);

        // Log processing statistics
        console.log("\nProcessing complete!");
        console.log(`Processed ${processedEncounters} encounters across ${processedLocations.size} locations`);
        console.log(`Output written to: ${outputFile}`);
        await log(`Processing complete!`);
        await log(`Processed ${processedEncounters} encounters across ${processedLocations.size} locations`);
        await log(`Output written to: ${outputFile}`);

    } catch (e) {
        console.log(`FATAL ERROR: ${e.message}`);
        await log(`Fatal error: ${e.message}`, 'ERROR');
        throw e;
    }
}

async function main() {
    const inputFile = '../src/data/wild_encounters.json';
    const outputFile = 'Wild_Encounters.xlsx';

    console.log("Starting encounter processing...");
    await log("Starting encounter processing...");

    try {
        await processEncounters(inputFile, outputFile);
        console.log("Processing completed successfully!");
        await log("Processing completed successfully!");
    } catch (e) {
        console.log("Processing failed!");
        await log("Processing failed!", 'ERROR');
        process.exitCode = 1;
    }

    // Keep window open
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    await new Promise(resolve => {
        rl.question('\nPress Enter to exit...', () => {
            rl.close();
            resolve();
        });
    });
}

main();