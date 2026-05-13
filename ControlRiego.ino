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
// --- INTEGRANTE 2: Módulo Analógico para YL-69 / FC-28 ---
void leerHumedad() {
  // Leer y mapear valor de 0-1023 a 0-100%

  // Leer el valor analógico crudo del sensor
  int valorSensor = analogRead(PIN_SENSOR_HUMEDAD);

  // Mapear el valor usando lógica INVERTIDA
  // 1023 (Tierra seca) -> 0% de humedad
  // 0 (Sumergido en agua) -> 100% de humedad
  humedadPorcentaje = map(valorSensor, 1023, 0, 0, 100);

  // Se limita el valor para evitar porcentajes negativos o mayores a 100%
  humedadPorcentaje = constrain(humedadPorcentaje, 0, 100);
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

// --- INTEGRANTE 5: Interfaz y Actuadores ---z
void actualizarPantalla() {

  // =====================================================
  // 1. Control del L298N
  // =====================================================

  if (bombaActivada) {

    // Activar motor
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // Velocidad mediante PWM
    analogWrite(ENA, 200);

  } else {

    // Detener motor
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    analogWrite(ENA, 0);
  }

  // =====================================================
  // 2. Mostrar datos en pantalla LCD
  // =====================================================

  lcd.clear();

  // Línea superior
  lcd.setCursor(0, 0);
  lcd.print("Humedad:");
  lcd.print(humedadPorcentaje);
  lcd.print("%");

  // Línea inferior
  lcd.setCursor(0, 1);

  if (modoManual) {
    lcd.print("Modo: MANUAL");
  } else {
    lcd.print("Modo: AUTO");
  }

  // Estado de la bomba
  if (bombaActivada) {
    lcd.print(" ON");
  } else {
    lcd.print(" OFF");
  }
}
