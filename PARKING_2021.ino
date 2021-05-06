  const int ocupada=8;
  const int libre=12;
  const int LEDblanco=11;
  const int LEDverde=10;
  const int LEDamarillo=7;
  const int LEDrojo=5;
  const int buzz=4;
  float duracion;
  float distancia;
  const int trigger=2;
  const int echo=3;
  float dist(float*,float*);
void setup() 
{
  pinMode(ocupada, OUTPUT);
  pinMode(libre, OUTPUT);
  pinMode(LEDblanco, OUTPUT);
  pinMode(LEDverde,OUTPUT);
  pinMode(LEDamarillo, OUTPUT);
  pinMode(LEDrojo, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzz,OUTPUT);
  Serial.begin(9600);
}

void loop() {

  
  digitalWrite(LEDverde, LOW);
  digitalWrite(LEDamarillo, LOW);
  digitalWrite(LEDrojo, LOW);
  digitalWrite(buzz,LOW);
  digitalWrite(trigger, HIGH);
  delay(1);
  distancia=dist(&distancia, &duracion);
  Serial.println("distancia:");
  Serial.println(distancia);
  delay(250);
  if(distancia>30)
  {
      digitalWrite(libre, HIGH);
      digitalWrite(ocupada, LOW);
  }
  if(distancia<30 && distancia>20)
  {
    digitalWrite(libre, HIGH);
    digitalWrite(ocupada, LOW);
    digitalWrite(LEDblanco, HIGH);
    digitalWrite(buzz, HIGH);
    tone(4,100,400);
    delay(400);
    digitalWrite(LEDblanco, LOW);
    digitalWrite(buzz, LOW);
    digitalWrite(LEDverde, LOW);
    digitalWrite(LEDamarillo, LOW);
    digitalWrite(LEDrojo, LOW);
  }
  if(distancia<20 && distancia>10)
  {
    digitalWrite(libre, HIGH);
    digitalWrite(ocupada, LOW);
    digitalWrite(LEDblanco, HIGH);
    digitalWrite(LEDverde, HIGH);
    digitalWrite(buzz,HIGH);
    tone(4,200,200);
    delay(200);
    digitalWrite(LEDblanco, LOW);
    digitalWrite(buzz, LOW);
    digitalWrite(LEDverde, LOW);
    digitalWrite(LEDamarillo, LOW);
    digitalWrite(LEDrojo, LOW);
  }
  if(distancia<10&&distancia>5)
  {
    digitalWrite(libre, HIGH);
    digitalWrite(ocupada, LOW);
     digitalWrite(LEDblanco, HIGH);
     digitalWrite(LEDverde, HIGH);
     digitalWrite(LEDamarillo, HIGH);
     digitalWrite(buzz, HIGH);
     tone(4,300,100);
     delay(100);
     digitalWrite(LEDblanco, LOW);
     digitalWrite(LEDverde, LOW);
     digitalWrite(LEDamarillo, LOW);
     digitalWrite(LEDrojo, LOW);
     digitalWrite(buzz,LOW);
  }
  if(distancia<5&&distancia>0)
  {
     digitalWrite(ocupada, HIGH);
     digitalWrite(libre, LOW);
     digitalWrite(buzz, HIGH);
     tone(4,380,0);
     delay(250);
     digitalWrite(LEDblanco, HIGH);
     delay(250);
     digitalWrite(LEDblanco, LOW);
     digitalWrite(LEDverde, HIGH);
     delay(250);
     digitalWrite(LEDverde, LOW);
     digitalWrite(LEDamarillo,HIGH);
     delay(250);
     digitalWrite(LEDamarillo, LOW);
     digitalWrite(LEDrojo, HIGH);
     delay(250);
     digitalWrite(LEDrojo, LOW);
     delay(250);
  }
 
    
}
float dist(float *distancia, float *duracion)
{
  digitalWrite(trigger, HIGH);
  delay(1);
  digitalWrite(trigger, LOW);
  *duracion=pulseIn(echo, HIGH);
  *distancia=*duracion/58.2;
  return *distancia;
}
