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
const int IN2 = 8; // Direction 2
const int ENA = 9; // Enable (PWM para velocidad)

// Pantalla LCD 16x2 (Pines: RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

// Variables globales de control
int humedadPorcentaje = 0;
bool modoManual = false;
bool bombaActivada = false;

// Variables de tiempo para el control asíncrono (Tu aporte)
unsigned long ultimoMuestreoSensor = 0;
const unsigned long INTERVALO_SENSOR = 1000; // Leer el sensor cada 1 segundo (1000 ms)

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
  lcd.begin(16, 2);
  lcd.print("Sistema Riego");
}

void loop() {
  // El botón se lee constantemente sin bloqueos para un debouncing perfecto
  leerBoton();
  
  // El sensor, la lógica y la pantalla se ejecutan de manera asíncrona cada 1 segundo
  if (millis() - ultimoMuestreoSensor >= INTERVALO_SENSOR) {
    ultimoMuestreoSensor = millis();
    
    leerHumedad();
    evaluarUmbral();
    actualizarPantalla();
  }
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
  
  // Depuración serial técnica exigida por la rúbrica (Tu aporte)
  Serial.print("ADC Raw: "); Serial.print(valorSensor);
  Serial.print(" -> Humedad Mapeada: "); Serial.print(humedadPorcentaje); Serial.println("%");
}

// --- INTEGRANTE 3: Módulo Digital y Debouncing ---
void leerBoton() {
  // Cambiar entre modo manual y automático con debouncing
}

// --- INTEGRANTE 4: Lógica y Umbral ---
void evaluarUmbral() {
  // Lógica de activación: si humedad < X% -> bombaActivada = true
}

// --- INTEGRANTE 5: Interfaz y Actuadores ---
void actualizarPantalla() {
  // 1. Control del L298N:
  if (bombaActivada) {
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW); 
    analogWrite(ENA, 200);
  } else {
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, LOW); 
    analogWrite(ENA, 0);
  }
  // 2. Mostrar datos en el LCD
}
