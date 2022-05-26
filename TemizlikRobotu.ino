//pin girişleri
#define sol_echoPin 2
#define sol_trigPin 3
#define on_echoPin 4
#define on_trigPin 5
#define sag_echoPin 6
#define sag_trigPin 7
//l298n motor gücünü ayarlama
#define in1 8
#define in2 9
#define in3 10
#define in4 11
#define ena 12
#define enb 13

int maximumRange = 50;
int minimumRange = 25;
int dcs = 255;
int sensor = 0;
void setup() {
  pinMode(on_echoPin,INPUT);
  pinMode(on_trigPin,OUTPUT);
  pinMode(sol_echoPin,INPUT);
  pinMode(sol_trigPin,OUTPUT);
  pinMode(sag_echoPin,INPUT);
  pinMode(sag_trigPin,OUTPUT);
  //motorlar çıkış tanımlanmalı
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  
  int sol_olcum = sol_mesafe(maximumRange,minimumRange);
  int on_olcum = on_mesafe(maximumRange,minimumRange);
  int sag_olcum = sag_mesafe(maximumRange,minimumRange);

Serial.print("sol: ");
Serial.print(sol_olcum);
Serial.print("  on: ");
Serial.print(on_olcum);
Serial.print("  sag:");
Serial.println(sag_olcum);
  
  
  
  
  char val = Serial.read();



  
  digitalWrite(ena , dcs);
  digitalWrite(enb , dcs);
  if(val == 'W'){ileri();}
  if(val == 'S'){geri();}
  if(val == 'A'){sol();}
  if(val == 'D'){sag();}
  if(val == 'Z'){dur();}
  if(val == 'T'){dcs=255;}
  if(val == 'Y'){dcs=155;}
  if(val == 'U'){dcs=55;}
  if(val == 'X'){sensor=1;}
   if(sensor>0){
    if(on_olcum < minimumRange || sol_olcum && sag_olcum < minimumRange){
      if(sol_olcum < sag_olcum)
      {geri();
       delay(200);
       sag();
       delay(300);}
       if(sag_olcum < sol_olcum){
        geri();
       delay(200);
       sol();
       delay(300);}
    }
    else if (sol_olcum < minimumRange) { 
      sag();
     delay(300);}
    else if (sag_olcum < minimumRange){
      sol();
     delay(300);}
    else if (sol_olcum && on_olcum && sag_olcum > minimumRange){
      ileri();}
     if(val == 'I'){ sensor=0; dur();}
    }
}
  

int sol_mesafe(int maxrange , int minrange){//sol sensörün mesafe ölçen fonksiyonu
  long duration , distance;

  digitalWrite(sol_trigPin,LOW);
  delayMicroseconds(3);
  digitalWrite(sol_trigPin,HIGH);
  delayMicroseconds(12);
  digitalWrite(sol_trigPin,LOW);

  duration = pulseIn(sol_echoPin,HIGH);
  distance = duration / 58.2;
  delay(50);
  return distance;
  }
int on_mesafe (int maxrange , int minrange){//on sensör
  long duration1 , distance1;
  digitalWrite(on_trigPin,LOW);
  delayMicroseconds(3);
  digitalWrite(on_trigPin,HIGH);
  delayMicroseconds(12);
  digitalWrite(on_trigPin,LOW);

  duration1 = pulseIn(on_echoPin,HIGH);
  distance1 = duration1 / 58.2;
  delay(50);
  return distance1;
  }
 int sag_mesafe (int maxrange , int mixrange){//sağ sensör
  long duration2,distance2;

  digitalWrite(sag_trigPin,LOW);
  delayMicroseconds(3);
  digitalWrite(sag_trigPin,HIGH);
  delayMicroseconds(12);
  digitalWrite(sag_trigPin,LOW);

  duration2 = pulseIn(sag_echoPin,HIGH);
  distance2 = duration2 / 58.2;
  delay(50);
  return distance2;
  }
  void dur(){   //robot durur.
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
  }
  void ileri(){   //robot ileri hareket eder.
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
  }
  void sag(){    //robot sağa döner.
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  }
  void sol(){   //robot sola döner.
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
  }
  void geri(){   //robot geri hareket eder.
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
  }
  
  
