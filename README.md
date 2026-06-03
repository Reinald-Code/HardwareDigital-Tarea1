# 💧 Sistema de Control de Riego Automatizado (ISF-215)

Este repositorio contiene el código fuente y la documentación para el **Sistema de Control de Riego**, correspondiente a la Tarea 1 de la asignatura ISF-215 Hardware Digital.

El sistema utiliza un Arduino UNO para monitorear la humedad del suelo y activar automáticamente una bomba de agua (simulada mediante un motor DC y un driver L298N) cuando los niveles caen por debajo de un umbral establecido. Se aplica histéresis (enciende bajo 40% y apaga sobre 60%) y en modo manual la bomba permanece apagada. Además, cuenta con una interfaz visual mediante una pantalla LCD 16x2 y un botón para alternar modos de funcionamiento.

## 👥 Integrantes del Equipo
* [Vicente Saa] - *Estructura Base*
* [Francisca Hernandez] - *Módulo Analógico (Sensor)*
* [Wilson Jara] - *Módulo Digital (Botón)*
* [Vicente Garcia] - *Lógica y Umbrales*
* [Sarai Herrera] - *Interfaz y Actuadores (LCD y L298N)*

## 🔌 Esquema de Conexiones (Pinout)

* **Sensor de Humedad (YL-69/FC-28):**
  * Pin de Señal Analógica (A0) a Pin A0 del Arduino.
* **Pulsador (Botón de Modo):**
  * Conectado al Pin Digital 12 (usando INPUT_PULLUP interno) y a GND.
* **Driver de Motor L298N (Control de Bomba):**
  * **IN1:** Pin Digital 9
  * **IN2:** Pin Digital 8
  * **ENA (PWM):** Pin Digital 10
  * *Nota:* Alimentado con pack de baterías externo de 12V. Tierras (GND) unificadas con el Arduino.
* **Pantalla LCD 16x2 (Modo paralelo):**
  * **RS:** Pin 7 | **EN:** Pin 6
  * **D4:** Pin 5  | **D5:** Pin 4
  * **D6:** Pin 3  | **D7:** Pin 2
  * *Contraste (V0):* Regulado mediante potenciómetro de 10 kΩ.

*(Nota: Se adjuntará el diagrama visual de Tinkercad/Wokwi en el informe técnico final).*

## 🚀 Instrucciones de Compilación y Uso

1. **Requisitos Previos:**
   * Tener instalado el [Arduino IDE](https://www.arduino.cc/en/software) (versión 2.x recomendada).
   * La librería estándar `LiquidCrystal` debe estar instalada (viene por defecto en el IDE).

2. **Clonar el Repositorio:**
   \`\`\`bash
   git clone https://github.com/Reinald-Code/HardwareDigital-Tarea1.git
   \`\`\`

3. **Compilación y Subida:**
   * Abre el archivo principal `ControlRiego.ino` en Arduino IDE.
   * Ve a **Herramientas > Placa** y selecciona **Arduino Uno**.
   * Ve a **Herramientas > Puerto** y selecciona el puerto COM correspondiente a tu placa conectada.
   * Haz clic en el botón **Verificar** (icono de check) para comprobar que el código compila sin errores.
   * Haz clic en **Subir** (icono de flecha derecha) para cargar el firmware al microcontrolador.
   
4. **Monitor Serie:**
   * Puedes abrir el Monitor Serie (a 9600 baudios) para visualizar los datos de depuración en tiempo real si el sistema lo requiere.
