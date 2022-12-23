#include <DHT.h>
//analogpins
#define DHT11_PIN A4
#define DHTTYPE DHT11
#define mq2_pin A1
#define LDR A3
#define rain A2

//digitalpins
int buzzer = 9;


void ReadDHT();
void  Readrain();
void  ReadAir();
void  Readlight();

DHT dht(DHT11_PIN, DHTTYPE);

float h,t;
int i,r;
void setup()
{
  Serial.begin(9600);
  pinMode(DHT11_PIN,INPUT);
  pinMode(mq2_pin, INPUT);
  pinMode(LDR, INPUT);
  pinMode(rain, INPUT);
  pinMode(buzzer, OUTPUT);
  //tone(buzzer,361);
}

void loop()
{
  ReadDHT();
  ReadAir();
  Readlight();
  Readrain();
  delay(5000);
}

void  ReadDHT(void)
{
  
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (isnan(h)|| isnan(t))
  {
    Serial.print("failed to read data from temp sensor");
    Serial.println("************************************");
  }
else if (t>45){
    for(i=0;i<=100;i++ )
      {      
        digitalWrite(buzzer,HIGH);
        delay(500);
        digitalWrite(buzzer,LOW);
        delay(500);        
      }
      Serial.print(h);
      Serial.print("%");
      Serial.println(t);
      Serial.print("C");
      Serial.println("************************************");
}  
else if (t<=45){
      Serial.print(h);
      Serial.print("%");
      Serial.println(t);
      Serial.print("C");
      Serial.println("************************************");      
} 
  delay(200);
}



void ReadAir(void)
{
  int airqlty = 0;
  Serial.print("AIR QUALITY:");
  airqlty = analogRead(mq2_pin);
  if (airqlty <= 180)
    Serial.print("GOOD!");
  else if (airqlty > 180 && airqlty <= 225)
    Serial.print("POOR");
  else if (airqlty > 225 && airqlty <= 300)
    Serial.print("VERY BAD");
  else{
    Serial.print("TOXIC");
    for(i=0;i<=100;i++ )
      {      
        digitalWrite(buzzer,HIGH);
        delay(500);
        digitalWrite(buzzer,LOW);
        delay(500);        
      }    
  }
  Serial.println("************************************");
  delay(200);
}

void Readrain()
{
 r = analogRead(rain);
 if(r >= 900)
 {
   Serial.print("it is raining !!");
   for(i=0;i<=100;i++ )
    {      
        digitalWrite(buzzer,HIGH);
        delay(500);
        digitalWrite(buzzer,LOW);
        delay(500);        
    }   
 }
 else
 {
   Serial.print("no rain currently!!");
 }
 delay(200);
}



void Readlight(void)
{
 
  Serial.print("LIGHT :");
  Serial.print(analogRead(LDR));
  Serial.print("%");
  Serial.print("************************************");
  delay(200);
}
