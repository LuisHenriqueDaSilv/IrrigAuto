#include <RTClib.h>

#include "eepromManager.h"
#include "utils.h"
#include "RTCController.h"
#include "routinesController.h"

#include "pages.h"

String Pages::landingPage(){
  std::list<RoutineStruct> routines = RoutinesController::getRoutines();
  NowStruct now = RTCController::getNow();
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
  
  buf += "  .optionButton {";
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
  buf += ".routine {";
  buf += "  display: flex;";
  buf += "  flex-direction: column;";
  buf += "  border: solid .5px #4039372a;";
  buf += "  border-radius: 10px;";
  buf += "  gap: 0;";
  buf += "  padding: 0.4rem;";
  buf += "}";
  buf += ".routine-infos {";
  buf += "  display: flex;";
  buf += "  flex-direction: row;";
  buf += "  justify-content: center;";
  buf += "  align-items: center;";
  buf += "  padding: .5rem;";
  buf += "  gap: 4rem;";
  buf += "}";
  buf += ".week-days {";
  buf += "  display: grid;";
  buf += "  width: 100%;";
  buf += "  height: 100%;";
  buf += "  grid-template-columns: repeat(7, 1fr);";
  buf += "  flex-direction: row;";
  buf += "  border: solid .5px #4039372a;";
  buf += "  border-radius: 10px;";
  buf += "}";
  buf += ".week-day {";
  buf += "  padding: 0.5rem;";
  buf += "  font-size: 1.6rem;";
  buf += "}";
  buf += ".disabled-week-day {";
  buf += "  opacity: 0.2;";
  buf += "  background: none;";
  buf += "}";
  
  buf += "  .routine p {";
  buf += "    font-size: 2rem;";
  buf += "  }";
  
  buf += "  .deleteRoutineButton {";
  buf += "    width: 4rem;";
  buf += "    height: 4rem;";
  buf += "    margin-left: auto;";
  buf += "    font-size: 1.5rem;";
  buf += "    background: #B55454;";
  buf += "    border: none;";
  buf += "    border-radius: 10px;";
  buf += "    cursor: pointer;";
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


  buf += ".manualButtonsContainer {";
  buf += "  display: grid;";
  buf += "  grid-template-columns: repeat(4, 1fr);";
  buf += "}";

  buf += ".manualButtonsContainer button:first-child {";
  buf += "  border-top-left-radius: 10px;";
  buf += "}";

  buf += ".manualButtonsContainer button:nth-child(4) {";
  buf += "  border-top-right-radius: 10px;";
  buf += "}";

  buf += ".manualButtonsContainer button:last-child {";
  buf += "  border-bottom-right-radius: 10px;";
  buf += "}";

  buf += ".manualButtonsContainer button:nth-child(4n + 1):nth-last-child(-n + 4) {";
  buf += "  border-bottom-left-radius: 10px;";
  buf += "}";

  buf += ".relayManualButton {";
  buf += "  border: 2px solid #ffffff;";
  buf += "  padding: 0.5rem;";
  buf += "  width: 8rem;";
  buf += "  border-radius: 0;";
  buf += "  color: #ffffff;";
  buf += "  background-color: #dfdfdf;";
  buf += "}";

  buf += ".relayManualButton h1 {";
  buf += "  font-size: 3rem;";
  buf += "  color: #ffffff;";
  buf += "}";

  buf += ".relayManualButton p {";
  buf += "	font-size: 1.5rem;";
  buf += "	color: #ffffff;";
  buf += "	font-weight: 600;";
  buf += "}";

  buf += ".relayManualButton label {";
  buf += "  color: #ffffff;";
  buf += "  font-size: 1.3rem;";
  buf += "}";

  buf += ".offButton {";
  buf += "  background-color: #A64D4D;";
  buf += "  color: #ffffff;";
  buf += "}";

  buf += ".onButton {";
  buf += "  color: #ffffff;";
  buf += "  background-color: #8AC87F;";
  buf += "}";

  buf += "header {";
  buf += "  display: flex;";
  buf += "  flex-direction: column;";
  buf += "  align-items: center;";
  buf += "  gap: 1rem;";
  buf += "}";

  buf += ".portIdentifier {";
    buf += "    width: 4rem;";
    buf += "    display: flex;";
    buf += "    flex-direction: column;";
    buf += "    justify-content: center;";
    buf += "    align-itens: center;";
    buf += "    height: 4rem;";
    buf += "    margin-right: auto;";
    buf += "    font-size: 1rem;";
    buf += "    border: none;";
    buf += "    border-radius: 10px;";
  buf += "}";

  buf += ".portIdentifier span {";
  buf += "  font-size: 8px;";
  buf += "}";

  buf += ".portIdentifier * {";
  buf += "  color: #ffffff;";
  buf += "}";

  buf += "header p {";
  buf += "  font-size: 1.3rem;";
  buf += "}";

  buf += ".day-of-week {";
  buf += "  border: solid .5px #4039372a;";
  buf += "  border-radius: 10px;";
  buf += "  padding: 1rem;";
  buf += "  font-size: 1.8rem;";
  buf += "}";

  buf += "</style>";
  
  buf += "<body>";
  buf += "  <div class='wrapper'>";
  buf += "    <div class='app'>";
  
  buf += "    <header class='header'>";
  buf += "      <div class='manualButtonsContainer'>";

  for(int i = 0; i<NUMBER_OF_RELAYS; i++){
    buf += "        <button class='relayManualButton ";
    if(relays[i].isOn){
      buf+="onButton";
    } else {
      buf+="offButton";
    }
    buf+="' ";
    buf+="id='relayManualButton-";
    buf+=numberToTwoChars(relays[i].id);
    buf+= "' ";
    buf+="onclick='manuallyTurnRelay("+String(relays[i].id)+")'\n";
    buf += "          <p>porta</p>";
    buf += "          <h1>"+String(relays[i].id)+"</h1>";
    buf += "          <label>";
    if(relays[i].isOn){
      buf+="ligado";
    } else {
      buf+="desligado";
    }
    buf+= "           </label>";
    buf += "        </button>";
  }

  buf += "      </div>";
  buf += "      <p>";
  buf += "        Toque em uma porta para alterar seu estado manualmente. A porta permanecerá nesse estado até que uma rotina ou nova alteração manual ocorra.";
  buf += "      </p>";
  buf += "    </header>  ";

  buf += "      <div class='routinesContainer'>";
  if(routines.size()){
    buf += "        <h1>rotinas configuradas</h1>";
    buf += "        <div class='routines'>";
    
    for(RoutineStruct routine: routines){
      bool relayIsOn = relays[routine.relayIndex-1].isOn;
      String routineDaysBinary = String(routine.days, BIN);
      if(routineDaysBinary.length() < 7){
        int numberOfZeros = 7 - routineDaysBinary.length();
        String complement = "";
        for(int i = 0; i< numberOfZeros; i++){
          complement+="0";
        }
        routineDaysBinary = complement+routineDaysBinary;
      }

      buf += "<div class='routine'>";
      buf += "        <div class='routine-infos'>";

      buf += "<div class='portIdentifier ";
      buf += "portIdentifierN-"; 
      buf += routine.relayIndex; 
      buf += " ";
      if(relayIsOn){
        buf+="onButton";
      } else {
        buf+="offButton";
      }
      buf += "'>";
      buf += "  <span>porta</span>";
      buf += "  <h1>";
      buf +=      numberToTwoChars(routine.relayIndex);
      buf += "  </h1>";
      buf += "</div>";
      
      buf += "            <p><strong>";
      buf += numberToTwoChars(routine.hourToTurnOn);
      buf += ":";
      buf += numberToTwoChars(routine.minuteToTurnOn);
      buf += "</strong> até <strong>";
      buf += numberToTwoChars(routine.hourToTurnOff);
      buf += ":";
      buf += numberToTwoChars(routine.minuteToTurnOff);
      buf += "</strong></p>";
      buf += "            <button ";
      buf += "              class='deleteRoutineButton'";
      buf += "              onclick='deleteRoutine(\"";
      buf += numberToTwoChars(routine.hourToTurnOn);
      buf += numberToTwoChars(routine.minuteToTurnOn);
      buf += numberToTwoChars(routine.hourToTurnOff);
      buf += numberToTwoChars(routine.minuteToTurnOff);
      buf += numberToTwoChars(routine.relayIndex);
      buf += routineDaysBinary;
      buf += "\")'";
      buf += "            > 🗑 </button>";
      buf += "        </div>";
      buf += "<div class='week-days'>";
      buf += String("  <div class='week-day ") + (routineDaysBinary.charAt(0) == '1' ? "onButton" : ".") + "'>D</div>";
      buf += String("  <div class='week-day ") + (routineDaysBinary.charAt(1) == '1' ? "onButton" : ".") + "'>S</div>";
      buf += String("  <div class='week-day ") + (routineDaysBinary.charAt(2) == '1' ? "onButton" : ".") + "'>T</div>";
      buf += String("  <div class='week-day ") + (routineDaysBinary.charAt(3) == '1' ? "onButton" : ".") + "'>Q</div>";
      buf += String("  <div class='week-day ") + (routineDaysBinary.charAt(4) == '1' ? "onButton" : ".") + "'>Q</div>";
      buf += String("  <div class='week-day ") + (routineDaysBinary.charAt(5) == '1' ? "onButton" : ".") + "'>S</div>";
      buf += String("  <div class='week-day ") + (routineDaysBinary.charAt(6) == '1' ? "onButton" : ".") + "'>S</div>";
      buf += "</div>";
      buf += "        </div>";
    }
      buf += "</div>";
  } else {
    buf += "        <h1>ainda não existe nenhuma rotina configurada</h1>";
  }
  buf += "        <div class='routinesFooter'>";
  buf += "          <a style='width:100%; heigth:100%;' href='/configurar-rotina'><button class='optionButton' style='width:100%'>adicionar rotina</button></a>";
  buf += "          <button class='optionButton' style='width:100%' onclick='clearRoutines()'>apagar rotinas</button>";
  buf += "        </div>";
  buf += "      </div>";
  
  buf += "      <div>";
  buf += "        <h1>data e hora:</h1>";
  buf += "        <div>";
  buf += "        <div id='day-of-week' class='day-of-week'>";
  buf += RTCController::weekDays[now.day];
  // buf += "          terça feira";
  buf += "        </div>";
  buf += "        <div class='clock'>";
  buf += "          <div id='currentHour'>";
  buf += numberToTwoChars(now.hour);
  buf += "          </div> <label class='clockSeparator'>:</label>";
  buf += "          <div id='currentMinute'>";
  buf += numberToTwoChars(now.minute);
  buf += "          </div>";
  buf += "        </div>";
  buf += "      </div>";
  buf += "      </div>";
  buf += "      <a href='/configurar-relogio'>configurar relogio</a>";
  buf += "      <a href='/rede'>configurar rede</a>";
  buf += "    </div>";
  buf += "  </div>";
  buf += "</body>";
  buf += "<script>";

  buf += "var socket = new WebSocket('ws://' + location.hostname + ':81/')\n";

  buf += "function updateRelayStatus({isOn, id}){\n";
  buf += "  const manualButton = window.document.getElementById(`relayManualButton-${id}`)\n";
  buf += "  const manualButtonSpan = manualButton.getElementsByTagName('label')[0]\n";
  buf += "  console.log(`portIdentifierN-${id}`)\n";
  buf += "  const portIdentifiers = window.document.getElementsByClassName(`portIdentifierN-${id}`)\n";
  buf += "  if (parseInt(isOn)) {\n";
  buf += "    for(var i = 0; i<portIdentifiers.length; i++){\n";
  buf += "      portIdentifiers[i].classList.remove('offButton')\n";
  buf += "      portIdentifiers[i].classList.add('onButton')\n";
  buf += "    }\n";
  buf += "    manualButton.classList.add('onButton')\n";
  buf += "    manualButton.classList.remove('offButton')\n";
  buf += "    manualButtonSpan.innerHTML = 'ligado'\n";
  buf += "  } else {\n";
  buf += "    manualButton.classList.remove('onButton')\n";
  buf += "    manualButton.classList.add('offButton')\n";
  buf += "    manualButtonSpan.innerHTML = 'desligado'\n";
  buf += "    for(var i = 0; i<portIdentifiers.length; i++){\n";
  buf += "      portIdentifiers[i].classList.remove('onButton')\n";
  buf += "      portIdentifiers[i].classList.add('offButton')\n";
  buf += "    }\n";
  buf += "  }\n";
  buf += "}\n";

  buf += "function updateClockDisplay(currentDate){\n";
  buf += "  window.document.getElementById('currentHour').innerHTML = currentDate.hora\n";
  buf += "  window.document.getElementById('currentMinute').innerHTML = currentDate.minuto\n";
  buf += "  window.document.getElementById('day-of-week').innerHTML = currentDate.dia\n";
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

  buf += "async function reloadPage(){\n";
  buf += "  location.reload()\n";
  buf += "}\n";

  buf += "async function deleteRoutine(routine) {\n";
  buf += "  const turnOnHour  = routine.slice(0, 2)\n";
  buf += "  const turnOnMinute = routine.slice(2, 4)\n";
  buf += "  const turnOffHour  = routine.slice(4, 6)\n";
  buf += "  const turnOffMinute = routine.slice(6, 8)\n";
  buf += "  const relayIndex = routine.slice(8, 10)\n";
  buf += "  const days = routine.slice(10, 17)\n";
  buf += "  const usuarioConfirmouAExclusao = confirm(`deseja mesmo excluir a rotina de ${turnOnHour}:${turnOnMinute} até ${turnOffHour}:${turnOffMinute}?`)\n";
  buf += "  if (usuarioConfirmouAExclusao) {\n";
  buf += "    const horarioFormatadoParaEnvio = `${turnOnHour}${turnOnMinute}${turnOffHour}${turnOffMinute}${relayIndex}`\n";
  buf += "    const response = await fetch(`/excluir-rotina?horario=${horarioFormatadoParaEnvio}&dias=${days}`);\n";
  buf += "    if(response.status!= 200){\n";
  buf += "      const data = await response.json()\n";
  buf += "      alert(data.message);\n";
  buf += "      return\n";
  buf += "    }\n";
  buf += "    reloadPage()\n";
  buf += "  }\n";
  buf += "}\n";

  buf += "async function manuallyTurnRelay(id){\n";
  buf += "  const response = fetch(`/mudar-rele?id=${id}`)\n";
  buf += "  if(response.status !== 200){\n";
  buf += "    const data = await response.json()\n";
  buf += "    alert(data.message)\n";
  buf += "    return\n";
  buf += "  }\n";
  buf += "}\n";

  buf += "async function clearRoutines(){\n";
  buf += "  const usuarioConfirmouAExclusao = confirm(`deseja mesmo excluir todas as rotinas configuradas??`)\n";
  buf += "  if (usuarioConfirmouAExclusao) {\n";
  buf += "    const response = await fetch('/apagar-rotinas')\n";
  buf += "    if(response.status != 200){\n";
  buf += "      const data = await response.json()\n";
  buf += "      alert('Algo de inesperado ocorreu')\n";
  buf += "      return\n";
  buf += "    }\n";
  buf += "    reloadPage()\n";
  buf += "  }\n";
  buf += "}\n";

  buf += "</script>";
  buf += "</body>";
  
  buf += "</html>";

  return buf;
}