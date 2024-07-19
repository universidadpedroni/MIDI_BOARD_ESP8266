#ifndef STYLES_CSS_H
#define STYLES_CSS_H
const char styles_css[] = R"rawliteral(
/* Estilos para el formulario y otros elementos */
body {
    font-family: Arial, sans-serif;
    background-color: #333;
    color: #fff;
    text-align: center;
    padding: 20px;
}

h1 {
    color: #ffcc00;
}
h2 {
    color: #ffcc00;
}
button {
            display: block;
            width: 200px;
            margin: 10px auto;
            padding: 15px;
            font-size: 16px;
            background-color: #444;
            color: #fff;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        button:hover {
            background-color: #555;
        }
        .update-button {
            margin-top: 30px;
            background-color: #ff5733;
        }
        .update-button:hover {
            background-color: #ff704d;
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
    font-size: 16px;
    background-color: #444;
    color: #fff;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    
}

/* Estilos específicos para el iframe oculto */
#iframe.hidden-form {
    display: none;
}
)rawliteral";

#endif