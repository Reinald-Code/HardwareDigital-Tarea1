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

// --- INTEGRANTE 2: Módulo Analógico ---
void leerHumedad() {
  // Leer y mapear valor de 0-1023 a 0-100%
}

// --- INTEGRANTE 3: Módulo Digital y Debouncing ---
void leerBoton() {
  // Cambiar entre modo manual y automático con debouncing
}

/**
 * --- INTEGRANTE 4: Lógica y Umbral ---
 * @brief Decide el estado de la bomba según el nivel de humedad y el modo de operación.
 * Si la humedad cae por debajo del 40%, se marca la bomba para ser activada.
 */
void evaluarUmbral() {
  // Solo aplicamos la lógica automática si el Modo Manual está desactivado
  if (modoManual == false) {
    
    if (humedadPorcentaje < 40) {
      // Si hay poca humedad, activamos la bomba
      bombaActivada = true; 
    } 
    else if (humedadPorcentaje > 60) {
      // HISTERESIS: Si ya llegó al 60%, dejamos de regar para no inundar
      bombaActivada = false;
    }
    // Si está entre 40 y 60, mantiene el estado anterior (evita que la bomba prenda/apague muy rápido)
    
  } else {
    // Si estamos en Modo Manual/OFF, la bomba siempre debe estar apagada por seguridad
    bombaActivada = false;
  }
}

// --- INTEGRANTE 5: Interfaz y Actuadores ---
void actualizarPantalla() {
  // 1. Control del L298N:
  //    Si bombaActivada: digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 200);
  //    Si no: analogWrite(ENA, 0);
  // 2. Mostrar datos en el LCD
}
