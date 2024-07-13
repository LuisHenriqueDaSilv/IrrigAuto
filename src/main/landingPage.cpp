#include <RTClib.h>

#include "eepromManager.h"
#include "utils.h"
#include "RTCController.h"

#include "pages.h"

String Pages::landingPage(){
  String routines = getRoutinesInEEPROM();
  int numberOfRoutines = getNumberOfRoutines(routines);
  std::array<int, 3> now = RTCController::getNow();
  String buf = ""; 

  buf += "<html lang='pt-BR'>";

  buf += "<head>";
  buf += "  <meta charset='UTF-8'>";
  buf += "  <meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  buf += "  <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  buf += "  <title>IrrigAuto</title>";
  buf += "</head>";
  buf += "<style>";
  buf += "  * {";
  buf += "    box-sizing: border-box;";
  buf += "    margin: 0;";
  buf += "    padding: 0;";
  buf += "    font-family: sans-serif;";
  buf += "    text-align: center;";
  buf += "    color: #403937;";
  buf += "  }";
  
  buf += "  :root {";
  buf += "    font-size: 62.5%;";
  buf += "  }";
  
  buf += "  body {";
  buf += "    background: linear-gradient(107.56deg, #5D5F28 0%, rgba(32, 90, 38, 0.557143) 32.29%, rgba(26, 87, 32, 0.264286) 53.65%, rgba(30, 30, 30, 0) 100%);";
  buf += "    background-color: #1E1E1E;";
  buf += "    overflow-x: hidden;";
  buf += "  }";
  
  buf += "  .wrapper {";
  buf += "    display: flex;";
  buf += "    align-items: center;";
  buf += "    justify-content: center;";
  buf += "  }";
  
  buf += "  .app {";
  buf += "    min-height: 100vh;";
  buf += "    max-width: 97.4rem;";
  buf += "    padding: 2rem 1rem;";
  buf += "    background-color: #D9D9D9;";
  buf += "    display: flex;";
  buf += "    flex-direction: column;";
  buf += "    align-items: center;";
  buf += "    gap: 3rem;";
  buf += "  }";
  
  buf += "  header {";
  buf += "    display: flex;";
  buf += "    flex-direction: column;";
  buf += "    align-items: center;";
  buf += "    gap: 1rem;";
  buf += "  }";
  
  buf += "  header span {";
  buf += "    font-size: 3.5rem;";
  buf += "    font-weight: 700;";
  buf += "    -webkit-text-stroke: .5px #403937a6;";
  buf += "  }";
  
  buf += "  header p {";
  buf += "    font-size: 1.3rem;";
  buf += "  }";
  
  buf += "  button {";
  buf += "    padding: 1rem;";
  buf += "    border: none;";
  buf += "    cursor: pointer;";
  buf += "    transition: 200ms;";
  buf += "    font-size: 1.6rem;";
  buf += "    border-radius: 10px;";
  buf += "    box-shadow: 0px 2px 2px rgba(0, 0, 0, 0.25);";
  buf += "    background: #C4C4C4;";
  buf += "  }";
  
  buf += "  button:hover {";
  buf += "    transform: scale(1.05);";
  buf += "    opacity: 0.7;";
  buf += "  }";
  
  buf += "  .on {";
  buf += "    color: #8AC880;";
  buf += "  }";
  
  buf += "  .off {";
  buf += "    color: #D45C5C;";
  buf += "  }";
  
  buf += "  .offButton {";
  buf += "    background-color: #8AC880;";
  buf += "    color: #ffffff;";
  buf += "  }";
  
  buf += "  .onButton {";
  buf += "    color: #ffffff;";
  buf += "    background-color: #D45C5C;";
  buf += "  }";
  
  buf += "  .routinesContainer {";
  buf += "    width: 90%;";
  buf += "    display: flex;";
  buf += "    flex-direction: column;";
  buf += "    align-items: center;";
  buf += "    gap: 1rem;";
  buf += "    border-radius: 10px;";
  buf += "    background-color: #cecece;";
  buf += "    box-shadow: 2px 2px 2px rgba(0, 0, 0, 0.25);";
  buf += "    padding: 1rem;";
  buf += "  }";
  
  buf += "  .routines {";
  buf += "    gap: 1rem;";
  buf += "    display: flex;";
  buf += "    flex-direction: column;";
  buf += "  }";
  
  buf += "  .routine {";
  buf += "    display: flex;";
  buf += "    flex-direction: row;";
  buf += "    justify-content: center;";
  buf += "    align-items: center;";
  buf += "    border: solid .5px #4039372a;";
  buf += "    border-radius: 10px;";
  buf += "    padding: .5rem;";
  buf += "    gap: 4rem;";
  buf += "  }";
  
  buf += "  .routine p {";
  buf += "    font-size: 2rem;";
  buf += "  }";
  
  buf += "  .deleteRoutineButton {";
  buf += "    width: 4rem;";
  buf += "    height: 4rem;";
  buf += "    margin-left: auto;";
  buf += "    font-size: 1.5rem;";
  buf += "    background: #B55454;";
  buf += "  }";
  
  buf += "  .routinesFooter {";
  buf += "    display: flex;";
  buf += "    flex-direction: column;";
  buf += "    align-items: center;";
  buf += "    gap: 1rem;";
  buf += "    width: 60%;";
  buf += "  }";
  
  buf += "  a {";
  buf += "    font-size: 1.5rem;";
  buf += "  }";
  
  buf += "  .clock {";
  buf += "    display: flex;";
  buf += "    justify-content: center;";
  buf += "    gap: 0.5rem;";
  buf += "    flex-direction: row;";
  buf += "    margin-top: 1rem;";
  buf += "    margin-bottom: 1rem;";
  buf += "  }";
  
  buf += "  .clock div {";
  buf += "    display: flex;";
  buf += "    justify-content: center;";
  buf += "    align-items: center;";
  buf += "    background-color: #CDCDCD;";
  buf += "    height: 5rem;";
  buf += "    width: 5rem;";
  buf += "    border-radius: 10px;";
  buf += "    font-size: 2rem;";
  buf += "  }";
  
  buf += "  .clockSeparator {";
  buf += "    font-size: 2rem;";
  buf += "    align-self: center;";
  buf += "  }";
  buf += "</style>";
  
  buf += "<body>";
  buf += "  <div class='wrapper'>";
  buf += "    <div class='app'>";
  
  buf += "      <header>";
  buf += "        <div>";
  buf += "          <h1>O dispositivo está </h1>";
  if(relay.isOn){
    buf += "          <span class='on' id='status'>ligado</span>";
  } else {
    buf += "          <span class='off' id='status'>desligado</span>";
  }
  buf += "        </div>";
  buf += "        <p>E permanecera assim até ser alterado por uma rotina configurada ou ser alterado manualmente.</p>";
  if(relay.isOn){
    buf += "        <button onclick='manuallyTurnRelay()' id='manualButton' class='onButton'>";
    buf += "          desligar manualmente";
    buf += "        </button>";
  } else {
    buf += "        <button onclick='manuallyTurnRelay()' id='manualButton' class='offButton'>";
    buf += "          ligar manualmente";
    buf += "        </button>";
  }
  buf += "      </header>";
  buf += "      <div class='routinesContainer'>";
  if(numberOfRoutines > 0){
    buf += "        <h1>rotinas configuradas</h1>";
    buf += "        <div class='routines'>";
    
    for(int i = 0; i < numberOfRoutines; i = i + 1){ 
      String turnOnHour = routines.substring(i*8, i*8+2);
      String turnOnMinute = routines.substring(i*8+2, i*8+4);
      String turnOffHour = routines.substring(i*8+4, i*8+6);
      String turnOffMinute = routines.substring(i*8+6, i*8+8);

      buf += "          <div class='routine'>";
      buf += "            <p><strong id='on'>";
      buf += turnOnHour;
      buf += ":";
      buf += turnOnMinute;
      buf += "</strong> até <strong id='off'>";
      buf += turnOffHour;
      buf += ":";
      buf += turnOffMinute;
      buf += "</strong></p>";
      buf += "            <button ";
      buf += "              class='deleteRoutineButton'";
      buf += "              onclick='deleteRoutine(\"";
      buf += turnOnHour;
      buf += turnOnMinute;
      buf += turnOffHour;
      buf += turnOffMinute;
      buf += "\")'";
      buf += "            > 🗑 </button>";
      buf += "        </div>";
    }
      buf += "</div>";
  } else {
    buf += "        <h1>ainda não existe nenhuma rotina configurada</h1>";
  }

  
  buf += "        <div class='routinesFooter'>";
  buf += "          <a style='width:100%; heigth:100%;' href='/configurar-rotina'><button style='width:100%'>adicionar rotina</button></a>";
  buf += "          <button style='width:100%' onclick='clearRoutines()'>apagar rotinas</button>";
  buf += "        </div>";
  buf += "      </div>";
  
  buf += "      <div>";
  buf += "        <h1>horario atual:</h1>";
  buf += "        <div class='clock'>";
  buf += "          <div id='currentHour'>";
  buf += numberToTwoChars(now[0]);
  buf += "          </div> <label class='clockSeparator'>:</label>";
  buf += "          <div id='currentMinute'>";
  buf += numberToTwoChars(now[1]);
  buf += "          </div>";
  buf += "        </div>";
  buf += "        <a href='/configurar-relogio'>configurar relogio</a>";
  buf += "      </div>";
  buf += "    </div>";
  buf += "  </div>";
  buf += "</body>";
  buf += "<script>";

  buf += "var socket = new WebSocket('ws://' + location.hostname + ':81/')\n";

  buf += "function updateRelayStatus(status){\n";
  buf += "  const statusDisplay = window.document.getElementById('status')\n";
  buf += "  const manualButton = window.document.getElementById('manualButton')\n";
  buf += "  if (status == 0) {\n";
  buf += "    statusDisplay.innerHTML = 'desligado'\n";
  buf += "    statusDisplay.className = 'off'\n";
  buf += "    manualButton.innerHTML = 'ligar manualmente'\n";
  buf += "    manualButton.className = 'offButton'\n";
  buf += "  } else {\n";
  buf += "    statusDisplay.innerHTML = 'ligado'\n";
  buf += "    statusDisplay.className = 'on'\n";
  buf += "    manualButton.innerHTML = 'desligar manualmente'\n";
  buf += "    manualButton.className = 'onButton'\n";
  buf += "  }\n";
  buf += "}\n";

  buf += "function updateClockDisplay(currentDate){\n";
  buf += "  window.document.getElementById('currentHour').innerHTML = currentDate.hora\n";
  buf += "  window.document.getElementById('currentMinute').innerHTML = currentDate.minuto\n";
  buf += "}\n";

  buf += "socket.onmessage = (event) => {\n";
  buf += "  console.log(event)\n";
  buf += "  const data = JSON.parse(event.data)\n";
  buf += "  switch (data.event) {\n";
  buf += "    case 'relayChange':\n";
  buf += "      updateRelayStatus(data.buffer)\n";
  buf += "      break;\n";
  buf += "    case 'clockUpdate':\n";
  buf += "      updateClockDisplay(data.buffer)\n";
  buf += "      break;\n";
  buf += "    default:\n";
  buf += "      console.log('Evento desconhecido');\n";
  buf += "  }\n";
  buf += "}\n";

  buf += "async function loadRoutines(){\n";
  buf += "  const routinesResponse = await fetch('/rotinas');\n";
  buf += "  const routinesResponseData = await routinesResponse.json()\n";
  buf += "  const routinesContainer = document.getElementsByClassName('routines')[0]\n";
  buf += "  routinesContainer.innerHTML = ''\n";
  buf += "if(routinesResponseData.number > 0){";
  buf += "  const routines = routinesResponseData.routines\n";
  buf += "  for(let i = 0; i< routinesResponseData.number; i++){\n";
  buf += "    const turnOnHour = routines.substring(i*8, i*8+2);\n";
  buf += "    const turnOnMinute = routines.substring(i*8+2, i*8+4);\n";
  buf += "    const turnOffHour = routines.substring(i*8+4, i*8+6);\n";
  buf += "    const turnOffMinute = routines.substring(i*8+6, i*8+8);\n";
  buf += "    document.getElementsByClassName('routines')[0].innerHTML += `\n";
  buf += "    <div class='routine'>\n";
  buf += "      <p><strong id='on'>${turnOnHour}:${turnOnMinute}</strong> até <strong id='off'>${turnOffHour}:${turnOffMinute}</strong></p>\n";
  buf += "      <button \n";
  buf += "        class='deleteRoutineButton'\n";
  buf += "        onclick='deleteRoutine(\"${turnOnHour}${turnOnMinute}${turnOffHour}${turnOffMinute}\")'\n";
  buf += "      > 🗑 </button>\n";
  buf += "    </div>\n";
  buf += "    `\n";
  buf += "  }\n";
  buf+= "} else {";
  buf+= "  routinesContainer.innerHTML = '<h1>ainda não existe nenhuma rotina configurada</h1>'";
  buf+= "}";
  buf += "}\n";

  buf += "async function deleteRoutine(routine) {\n";
  buf += "  const turnOnHour  = routine.slice(0, 2)\n";
  buf += "  const turnOnMinute = routine.slice(2, 4)\n";
  buf += "  const turnOffHour  = routine.slice(4, 6)\n";
  buf += "  const turnOffMinute = routine.slice(6, 8)\n";
  buf += "  const usuarioConfirmouAExclusao = confirm(`deseja mesmo excluir a rotina de ${turnOnHour}:${turnOnMinute} até ${turnOffHour}:${turnOffMinute}?`)\n";
  buf += "  if (usuarioConfirmouAExclusao) {\n";
  buf += "    const horarioFormatadoParaEnvio = `${turnOnHour}${turnOnMinute}${turnOffHour}${turnOffMinute}`\n";
  buf += "    const response = await fetch(`/excluir-rotina?horario=${horarioFormatadoParaEnvio}`);\n";
  buf += "    loadRoutines()\n";
  buf += "    fetchDatas()\n";
  buf += "  }\n";
  buf += "}\n";

  buf += "function manuallyTurnRelay(){\n";
  buf += "  socket.send('mudar-rele')\n";
  buf += "}\n";

  buf += "async function clearRoutines(){\n";
  buf += "  const usuarioConfirmouAExclusao = confirm(`deseja mesmo excluir todas as rotinas configuradas??`)\n";
  buf += "  if (usuarioConfirmouAExclusao) {\n";
  buf += "    const response = await fetch('/apagar-rotinas')\n";
  buf += "    if(response.status == 200){\n";
  buf += "      loadRoutines()\n";
  buf += "    }\n";
  buf += "  }\n";
  buf += "}\n";

  buf += "</script>";
  buf += "</body>";
  
  buf += "</html>";

  return buf;
}