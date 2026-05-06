// =========================================================
// ISF-215: Tarea 1 - Hardware Digital
// Sistema: Control de Riego con L298N y LCD 16x2
// =========================================================
#include <LiquidCrystal.h>

// --- INTEGRANTE 1: Estructura base y pines ---
// Entradas
const int PIN_SENSOR_HUMEDAD = A0;
const int PIN_BOTON = 2;

// Salidas: Control del Motor (L298N)
const int IN1 = 7; // Dirección 1
const int IN2 = 8; // Dirección 2
const int ENA = 9; // Enable (PWM para velocidad)

// Pantalla LCD 16x2 (Pines: RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

// Variables globales
int humedadPorcentaje = 0;
bool modoManual = false;
bool bombaActivada = false;

void setup() {
  Serial.begin(9600);
  
  // Configuración de pines
  pinMode(PIN_SENSOR_HUMEDAD, INPUT);
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Inicialización de actuadores
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  // Integrante 5: Iniciar LCD aquí
}

void loop() {
  leerHumedad();
  leerBoton();
  evaluarUmbral();
  actualizarPantalla();
  delay(100); 
}

// --- INTEGRANTE 2: Módulo Analógico para YL-69 / FC-28 ---
void leerHumedad() {
  // Leer el valor analógico crudo del sensor
  int valorSensor = analogRead(PIN_SENSOR_HUMEDAD);

  // Mapear el valor usando lógica INVERTIDA
  // 1023 (Tierra seca) -> 0% de humedad
  // 0 (Sumergido en agua) -> 100% de humedad
  humedadPorcentaje = map(valorSensor, 1023, 0, 0, 100);

  // Se limita el valor para evitar porcentajes negativos o mayores a 100%
  humedadPorcentaje = constrain(humedadPorcentaje, 0, 100);




}
// --- Módulo Digital y Debouncing ---
void leerBoton() {
  // Comprobamos si el botón está presionado Y si han pasado más de 200ms desde el último cambio
  if (digitalRead(PIN_BOTON) == LOW && (millis() - ultimoTiempoBoton > 200)) {
    
    modoManual = !modoManual;       // Cambia el modo (Toggle)
    ultimoTiempoBoton = millis();   // Actualiza el tiempo de la última pulsación
    

    Serial.print("Modo cambiado a: ");
    Serial.println(modoManual ? "MANUAL" : "AUTO");
  }
}


}
}
// --- INTEGRANTE 4: Lógica y Umbral ---
void evaluarUmbral() {
  // Lógica de activación: si humedad < X% -> bombaActivada = true
}

// --- INTEGRANTE 5: Interfaz y Actuadores ---
void actualizarPantalla() {
  // 1. Control del L298N:
  //    Si bombaActivada: digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 200);
  //    Si no: analogWrite(ENA, 0);
  // 2. Mostrar datos en el LCD
}