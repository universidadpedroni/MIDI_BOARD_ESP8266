#include "htmlContent.h"

const char* htmlPage = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>MIDI Controller</title>
        <link rel="stylesheet" href="styles.css">
    </head>
    <body>
        <div class="container">
            <h1>MIDI Controller Configuration</h1>
            <div class="button-container">
                <label for="switch-selector">Select a Switch:</label>
                <select id="switch-selector" onchange="showSettings()">
                    <option value="switch1">Switch 1</option>
                    <option value="switch2">Switch 2</option>
                    <option value="switch3">Switch 3</option>
                    <option value="switch4">Switch 4</option>
                    <option value="switch5">Switch 5</option>
                    <option value="switch6">Switch 6</option>
                    <option value="switch7">Switch 7</option>
                </select>
            </div>
            <div class="settings-container" id="settings-container">
                %SETTINGS_SECTIONS%
            </div>
        </div>
        <script>
            // Valores por defecto para cada switch
            const defaultValues = {
                switch1: { midiChannel: 1, pcCc: "PC", value: 64, toggleValue: 0 },
                switch2: { midiChannel: 2, pcCc: "CC", value: 100, toggleValue: 127 },
                switch3: { midiChannel: 3, pcCc: "PC", value: 32, toggleValue: 0 },
                switch4: { midiChannel: 4, pcCc: "CC", value: 80, toggleValue: 127 },
                switch5: { midiChannel: 5, pcCc: "PC", value: 16, toggleValue: 0 },
                switch6: { midiChannel: 6, pcCc: "CC", value: 120, toggleValue: 127 },
                switch7: { midiChannel: 7, pcCc: "PC", value: 8, toggleValue: 0 }
            };

            // Función para cargar valores por defecto según el switch seleccionado
            function loadDefaultValues(switchId) {
                const { midiChannel, pcCc, value, toggleValue } = defaultValues[switchId];

                document.getElementById(`midi-channel`).value = midiChannel;
                document.getElementById(`pc-cc`).value = pcCc;
                document.getElementById(`value`).value = value;
                document.getElementById(`toggle-value`).checked = toggleValue === 127;
            }

            // Función para mostrar la configuración del switch seleccionado
            function showSettings() {
                const switchId = document.getElementById("switch-selector").value;
                const settingsContainer = document.getElementById("settings-container");

                // Construir el HTML de la sección de configuración según el switch seleccionado
                const settingsHtml = `
                    <div id="${switchId}-settings" class="settings">
                        <h2>Settings for ${switchId}</h2>
                        <label for="midi-channel">MIDI Channel:</label>
                        <select id="midi-channel">
                            ${generateMidiChannelsOptions()}
                        </select>
                        <label for="pc-cc">PC or CC:</label>
                        <select id="pc-cc">
                            <option value="PC">PC</option>
                            <option value="CC">CC</option>
                        </select>
                        <label for="value">Value:</label>
                        <input type="number" id="value" min="0" max="127">
                        <label for="toggle-value">Toggle Value (0/127):</label>
                        <input type="checkbox" id="toggle-value">
                        <button onclick="updateSettings('${switchId}')">Save</button>
                    </div>
                `;

                settingsContainer.innerHTML = settingsHtml;

                // Cargar valores por defecto al mostrar la configuración
                loadDefaultValues(switchId);
            }

            // Generar opciones para MIDI Channel (1-16)
            function generateMidiChannelsOptions() {
                let options = '';
                for (let i = 1; i <= 16; i++) {
                    options += `<option value="${i}">${i}</option>`;
                }
                return options;
            }

            // Función para actualizar configuraciones al guardar cambios
            function updateSettings(switchId) {
                const midiChannel = document.getElementById(`midi-channel`).value;
                const pcCc = document.getElementById(`pc-cc`).value;
                const value = document.getElementById(`value`).value;
                const toggleValue = document.getElementById(`toggle-value`).checked ? 127 : 0;

                if (midiChannel < 1 || midiChannel > 16) {
                    alert("MIDI Channel must be between 1 and 16.");
                    return;
                }

                if (pcCc !== "PC" && pcCc !== "CC") {
                    alert('PC or CC must be either "PC" or "CC".');
                    return;
                }

                const data = {
                    midiChannel,
                    pcCc,
                    value,
                    toggleValue
                };

                fetch('/save', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify(data)
                }).then(response => {
                    if (response.ok) {
                        alert(`Settings for ${switchId} saved successfully!`);
                    } else {
                        alert(`Failed to save settings for ${switchId}.`);
                    }
                });
            }

            // Mostrar la configuración del primer switch al cargar la página
            document.addEventListener('DOMContentLoaded', () => {
                showSettings();
            });
        </script>
    </body>
    </html>
)rawliteral";

const char* settingsSections = "";


