#ifndef STYLES_CSS_H
#define STYLES_CSS_H
const char styles_css[] = R"rawliteral(
/* Estilos para el formulario y otros elementos */
body {
    font-family: Arial, Helvetica, sans-serif;
    background-color: #222; /* Dark grey background */
    color: #eee; /* Light text color */
    padding: 20px;
}

h2 {
    color: #4CAF50; /* Greenish accent color */
}

form {
    background-color: #333; /* Darker grey form background */
    color: #eee; /* Light text color */
    padding: 10px;
    border-radius: 5px;
    box-shadow: 0 0 10px rgba(0,0,0,0.5); /* Slightly heavier shadow */
    margin-bottom: 20px;
}

select, input[type="number"], input[type="submit"] {
    padding: 10px;
    margin: 5px 0;
    width: 100%;
    border: 1px solid #555; /* Darker border */
    border-radius: 3px;
    box-sizing: border-box;
    background-color: #444; /* Darker input background */
    color: #eee; /* Light text color */
}

input[type="submit"] {
    background-color: #4CAF50; /* Green button */
    cursor: pointer;
    border: none;
    font-size: 16px;
}

/* Estilos específicos para el iframe oculto */
#iframe.hidden-form {
    display: none;
}
)rawliteral";

#endif