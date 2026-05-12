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
bool estadoBotonAnterior = HIGH;
bool estadoBotonEstable = HIGH;
unsigned long ultimoCambioBoton = 0;
const unsigned long DEBOUNCE_MS = 50;

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

// --- INTEGRANTE 2: Módulo Analógico ---
void leerHumedad() {
  // Leer y mapear valor de 0-1023 a 0-100%
}

// --- INTEGRANTE 3: Módulo Digital y Debouncing ---
void leerBoton() {
  // Cambiar entre modo manual y automático con debouncing
  bool lecturaBoton = digitalRead(PIN_BOTON);

  if (lecturaBoton != estadoBotonAnterior) {
    ultimoCambioBoton = millis();
  }

  if ((millis() - ultimoCambioBoton) > DEBOUNCE_MS) {
    if (lecturaBoton != estadoBotonEstable) {
      estadoBotonEstable = lecturaBoton;

      if (estadoBotonEstable == LOW) {
        modoManual = !modoManual;
      }
    }
  }

  estadoBotonAnterior = lecturaBoton;
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