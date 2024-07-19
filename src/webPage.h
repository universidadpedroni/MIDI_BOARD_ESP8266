#ifndef WEBPAGE_H
#define WEBPAGE_H

const char index_html[] = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
    <title>MIDI BOARD SWITCHER CONFIG</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        %style
    </style>
</head>
<body>
    <h2>MIDI BOARD SWITCHER CONFIG</h2>
    
    <section>
        <button onclick="location.href='/switch0'">Switch 1</button><br>
        <button onclick="location.href='/switch1'">Switch 2</button><br>
        <button onclick="location.href='/switch2'">Switch 3</button><br>
        <button onclick="location.href='/switch3'">Switch 4</button><br>
        <button onclick="location.href='/switch4'">Switch 5</button><br>
        <button onclick="location.href='/switch5'">Switch 6</button><br>
        <button onclick="location.href='/switch6'">Switch 7</button><br>
        <button onclick="location.href='/update'">Update</button>
    </section>
    <p>Compilation Date and TIme: %__DATE__, %__TIME__</p>
</body>
</html>
)rawliteral";



const char switch_html[]  = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
    <title>ESP Input Form</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        %style
    </style>
    <script>
        function submitMessage() {
            alert("Valor Actualizado");
            setTimeout(function(){ document.location.reload(false); }, 500);
        }
    </script>
</head>
<body>
    <h2>Switch %idSwitch</h2>
    <section>
        <form action="/get" method="get">
        
            MIDI Channel: 
            <select name="PB_MIDI_CH">
                <option value="1" %PB_MIDI_CH_1%>1</option>
                <option value="2" %PB_MIDI_CH_2%>2</option>
                <option value="3" %PB_MIDI_CH_3%>3</option>
                <option value="4" %PB_MIDI_CH_4%>4</option>
                <option value="5" %PB_MIDI_CH_5%>5</option>
                <option value="6" %PB_MIDI_CH_6%>6</option>
                <option value="7" %PB_MIDI_CH_7%>7</option>
                <option value="8" %PB_MIDI_CH_8%>8</option>
                <option value="9" %PB_MIDI_CH_9%>9</option>
                <option value="10" %PB_MIDI_CH_10%>10</option>
                <option value="11" %PB_MIDI_CH_11%>11</option>
                <option value="12" %PB_MIDI_CH_12%>12</option>
                <option value="13" %PB_MIDI_CH_13%>13</option>
                <option value="14" %PB_MIDI_CH_14%>14</option>
                <option value="15" %PB_MIDI_CH_15%>15</option>
                <option value="16" %PB_MIDI_CH_16%>16</option>
            </select>
            <input type="hidden" name="buttonIndex" value="%idSwitch%">
            <input type="submit" value="Submit" onclick="submitMessage()">
        </form><br>

        <form action="/get" method="get">
        
            CC / PC: 
            <select name="PB_CC_PC">
                <option value="CC" %PB_CC%>CC</option>
                <option value="PC" %PB_PC%>PC</option>
            </select>
            <input type="hidden" name="buttonIndex" value="%idSwitch%">
            <input type="submit" value="Submit" onclick="submitMessage()">
        </form><br>
        
        <form action="/get" method="get">
        
            Value: 
            <input type="number" name="PB_VALUE" min="0" max="127" value="%pushButton0Value%">
            <input type="hidden" name="buttonIndex" value="%idSwitch%">
            <input type="submit" value="Submit" onclick="submitMessage()">
        </form><br>

        
        <form action="/get" method="get">
        
            Toggle Value?: 
            <select name="PB_TOGGLE">
                <option value="Yes" %PB_Yes%>Yes</option>
                <option value="No" %PB_No%>No</option>
            </select>
            <input type="hidden" name="buttonIndex" value="%idSwitch%">
            <input type="submit" value="Submit" onclick="submitMessage()">
        </form><br>
    
    <button onclick="location.href='/'">Volver</button>
    
    <iframe style="display:none" name="hidden-form"></iframe>


    </section>
</body>
</html>
)rawliteral";




#endif

