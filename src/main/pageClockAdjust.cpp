#include "pages.h"

String Pages::clockAdjustPage(){
  String buf = "";
  buf += "<!DOCTYPE html>";
  buf += "<html lang='pt-BR'>";
  buf += "<head>";
  buf += "    <meta charset='UTF-8'>";
  buf += "    <meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  buf += "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  buf += "    <title>IrrigAuto</title>";
  buf += "</head>";
  buf += "<style>";
  buf += "* {";
  buf += "  box-sizing: border-box;";
  buf += "  margin: 0;";
  buf += "  padding: 0;";
  buf += "  font-family: 'Inter', sans-serif;";
  buf += "  text-align: center;";
  buf += "  color: #403937;";
  buf += "}";
  buf += ":root {";
  buf += "  font-size: 62.5%;";
  buf += "}";
  buf += "body {";
  buf += "  width: 100vw;";
  buf += "  height: 100vh;";
  buf += "  background: linear-gradient(107.56deg, #5D5F28 0%, rgba(32, 90, 38, 0.557143) 32.29%, rgba(26, 87, 32, 0.264286) 53.65%,";
  buf += "      rgba(30, 30, 30, 0) 100%);";
  buf += "  background-color: #1E1E1E;";
  buf += "}";
  buf += ".wrapper {";
  buf += "  display: flex;";
  buf += "  align-items: center;";
  buf += "  justify-content: center;";
  buf += "}";
  buf += ".app {";
  buf += "  min-height: 100vh;";
  buf += "  max-width: 97.4rem;";
  buf += "  width: 100%;";
  buf += "  padding: 2rem 1rem;";
  buf += "  background-color: #D9D9D9;";
  buf += "  display: flex;";
  buf += "  flex-direction: column;";
  buf += "  align-items: center;";
  buf += "  gap: 3rem;";
  buf += "}";
  buf += ".timer {";
  buf += "  display: flex;";
  buf += "  flex-direction: row;";
  buf += "  align-items: center;";
  buf += "  gap: 0.3rem;";
  buf += "}";
  buf += ".timer-container {";
  buf += "  display: flex;";
  buf += "  flex-direction: column;";
  buf += "}";
  buf += ".timer-container div {";
  buf += "  display: flex;";
  buf += "  justify-content: center;";
  buf += "  align-items: center;";
  buf += "  width: 6rem;";
  buf += "  height: 6rem;";
  buf += "  background: #CDCDCD;";
  buf += "  box-shadow: inset 4px 4px 4px rgba(0, 0, 0, 0.25);";
  buf += "  font-size: 4rem;";
  buf += "}";
  buf += ".timer-container button {";
  buf += "  margin-top: 0.2rem;";
  buf += "  width: 100%;";
  buf += "  height: 6rem;";
  buf += "  background: #8AC880;";
  buf += "  border: none;";
  buf += "  box-shadow: 0px 4px 4px rgba(0, 0, 0, 0.25);";
  buf += "  font-weight: 900;";
  buf += "  font-size: 36px;";
  buf += "  color: #ffffff;";
  buf += "  cursor: pointer;";
  buf += "  transition: 200ms;";
  buf += "}";
  buf += ".timer-container button:first-child {";
  buf += "  border-radius: 10px 10px 0 0;";
  buf += "}";
  buf += ".timer-container button:last-child {";
  buf += "  border-radius: 0 0 10px 10px;";
  buf += "}";
  buf += ".timer p {";
  buf += "  font-size: 4rem;";
  buf += "}";
  buf += ".footer {";
  buf += "  display: flex;";
  buf += "  width: 100%;";
  buf += "  max-width: 97.4rem;";
  buf += "}";
  buf += ".footer button {";
  buf += "  border: 0;";
  buf += "  border-radius: 10px 0 0 10px;";
  buf += "  width: 100%;";
  buf += "  padding: 1rem;";
  buf += "  background-color: #3B64B2;";
  buf += "  color: #FFFFFF;";
  buf += "  font-weight: 700;";
  buf += "  font-size: 2rem;";
  buf += "  text-decoration: none;";
  buf += "  transition: 200ms;";
  buf += "  cursor: pointer;";
  buf += "}";
  buf += "#cancel-button {";
  buf += "  border-radius: 0 10px 10px 0;";
  buf += "  background-color: #B2433B;";
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
  buf += "  cursor: pointer;";
  buf += "  border: solid .5px #4039372a;";
  buf += "  padding: 0.5rem;";
  buf += "  font-size: 1.6rem;";
  buf += "  display: flex;";
  buf += "  justify-content: center;";
  buf += "  align-itens: center;";
  buf += "  background: none;";
  buf += "}";

  buf += "#selected-week-day {";
  buf += "  color: #ffffff;";
  buf += "  background-color: #8AC87F;";
  buf += "}";

  buf += "</style>";
  buf += "<body>";
  buf += "    <div class='wrapper'>";
  buf += "        <div class='app'>";
  buf += "            <h1>configure a data e hora atual</h1>";
  buf += "            <h1>dia de hoje:</h1>";
  buf += "            <div class='week-days'>";
  buf += "              <button class='week-day day-0' id='selected-week-day' onclick='selecionarDia(0)'>D</button>";
  buf += "              <button class='week-day day-1' onclick='selecionarDia(1)'>S</button>";
  buf += "              <button class='week-day day-2' onclick='selecionarDia(2)'>T</button>";
  buf += "              <button class='week-day day-3' onclick='selecionarDia(3)'>Q</button>";
  buf += "              <button class='week-day day-4' onclick='selecionarDia(4)'>Q</button>";
  buf += "              <button class='week-day day-5' onclick='selecionarDia(5)'>S</button>";
  buf += "              <button class='week-day day-6' onclick='selecionarDia(6)'>S</button>";
  buf += "            </div>";

  buf += "            <h1>horario atual:</h1>";
  buf += "            <div class='timer'>";
  buf += "                <div class='timer-container'>";
  buf += "                    <button onclick='somarHora(5)'>+5</button>";
  buf += "                    <button onclick='somarHora(1)'>+1</button>";
  buf += "                    <div id='hora'>00</div>";
  buf += "                    <button onclick='somarHora(-1)' style='background-color: #D45C5C;'>-1</button>";
  buf += "                    <button onclick='somarHora(-5)' style='background-color: #D45C5C;'>-5</button>";
  buf += "                </div>";
  buf += "                <p>:</p>";
  buf += "                <div class='timer-container'>";
  buf += "                    <button onclick='somarMinutos(5)'>+5</button>";
  buf += "                    <button onclick='somarMinutos(1)'>+1</button>";
  buf += "                    <div id='minuto'>00</div>";
  buf += "                    <button onclick='somarMinutos(-1)' style='background-color: #D45C5C;'>-1</button>";
  buf += "                    <button onclick='somarMinutos(-5)' style='background-color: #D45C5C;'>-5</button>";
  buf += "                </div>";
  buf += "            </div>";
  buf += "              <div class='footer'>";
  buf += "                <button onclick='confirmar()'>confirmar</button>";
  buf += "                <button onclick='cancelar()' id='cancel-button'>cancelar</button>";
  buf += "            </div>";
  buf += "        </div>";
  buf += "    </div>";
  buf += "</body>";
  buf += "<script>";
  buf += "  let horas = 0\n";
  buf += "  let minutos = 0\n";
  buf += "  let dia = 0\n";
  buf += "  function atualizarDisplay() {\n";
  buf += "      const displayMinutos = window.document.getElementById('minuto')\n";
  buf += "      const displayHoras = window.document.getElementById('hora')\n";
  buf += "      displayMinutos.innerHTML = minutos\n";
  buf += "      displayHoras.innerHTML = horas\n";
  buf += "  }\n";
  buf += "  function somarHora(valor) {\n";
  buf += "      if (horas + valor > 23) {\n";
  buf += "          horas = 0\n";
  buf += "      } else if (horas + valor < 0) {\n";
  buf += "          horas = 23\n";
  buf += "      } else {\n";
  buf += "          horas = horas + valor\n";
  buf += "      }\n";
  buf += "      atualizarDisplay()\n";
  buf += "  }\n";
  buf += "  function somarMinutos(valor) {\n";
  buf += "      if (minutos + valor > 59) {\n";
  buf += "          minutos = 0\n";
  buf += "      } else if (minutos + valor < 0) {\n";
  buf += "          minutos = 59\n";
  buf += "      } else {\n";
  buf += "          minutos = minutos + valor\n";
  buf += "      }\n";
  buf += "      atualizarDisplay()\n";
  buf += "  }";
  buf += "  function selecionarDia(id){\n";
  buf += "    const selectedDay = window.document.getElementById('selected-week-day');\n";
  buf += "    if(selectedDay){\n";
  buf += "      selectedDay.id = '';\n";
  buf += "    }\n";
  buf += "    const newSelectedDay = window.document.getElementsByClassName(`day-${id}`)[0]\n";
  buf += "    newSelectedDay.id = 'selected-week-day'\n";
  buf += "    dia = id;\n";
  buf += "  }\n";
  buf += "  function cancelar(){\n";
  buf += "      window.location.replace('/')\n";
  buf += "  }\n";
  buf += "  async function confirmar(){\n";
  buf += "    const response = await fetch(`/setar-relogio?hora=${horas}&minuto=${minutos}&dia=${dia}`);\n";
  buf += "    if(response.status !== 200){\n";
  buf += "      const data = await response.json()\n";
  buf += "      alert(data.message);\n";
  buf += "      return;\n";
  buf += "    }\n";
  buf += "    window.location.replace('/')\n";
  buf += "  }\n";
  buf += "</script>";
  buf += "</html>";
  return buf;
}