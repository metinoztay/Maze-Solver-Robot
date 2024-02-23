//IR Sensor
const int sagTrigPin = A4;
const int sagEchoPin = A5;
const int ortaTrigPin = A2;
const int ortaEchoPin = A3;
const int solTrigPin = A0;
const int solEchoPin = A1;
//Motor Sürücü
const int solileri = 7;
const int solgeri = 6;
const int sagileri = 5;
const int saggeri = 4;
const int solenable = 9;
const int sagenable = 10;
//
#define BUTTON_PIN 2
int sayac = 0;
//IR Sensor Değişkenleri
long sure;
int uzaklik;
int guvenlikMesafesi;
int soluzaklik;
int ortauzaklik;
int saguzaklik;
//uzaklık dizisi
bool secimNoktasiMi = false;
int yolSayaci;
char secilenYol;
char yollar[3];

void setup() {
  Serial.begin(9600);
  //IR Setup
  pinMode(sagTrigPin, OUTPUT);
  pinMode(sagEchoPin, INPUT);
  pinMode(ortaTrigPin, OUTPUT);
  pinMode(ortaEchoPin, INPUT);
  pinMode(solTrigPin, OUTPUT);
  pinMode(solEchoPin, INPUT);
  pinMode(BUTTON_PIN, INPUT); //buton input
  //Motor Surucu
  pinMode(sagenable, OUTPUT);
  pinMode(solenable, OUTPUT);
  pinMode(sagileri, OUTPUT);
  pinMode(saggeri, OUTPUT);
  pinMode(solileri, OUTPUT);
  pinMode(solgeri, OUTPUT);
}

void loop() {
  ButonSayac();
  if (sayac > 0) {
    UzaklikKontroluYap();
    UzakliklariYaz();
    SolDuvarIzle();
  }
  else
  {
    UzaklikKontroluYap();
    UzakliklariYaz();
    delay(500);
  }
}


void SolDuvarIzle(){  
  if(soluzaklik>=80 && ortauzaklik>=80 && saguzaklik>=80) //3 yol
  {
    Dur();
    delay(5);
    digitalWrite(solileri, HIGH);
    digitalWrite(solgeri, LOW);
    digitalWrite(sagileri, HIGH);
    digitalWrite(saggeri, LOW);
    delay(5);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, LOW);
    digitalWrite(sagileri, LOW);
    digitalWrite(saggeri, LOW);
    delay(2);
    SolaDon();
    delay(10);
    digitalWrite(solileri, HIGH);
    digitalWrite(solgeri, LOW);
    digitalWrite(sagileri, HIGH);
    digitalWrite(saggeri, LOW);
    delay(5);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, LOW);
    digitalWrite(sagileri, LOW);
    digitalWrite(saggeri, LOW);
    delay(2);
  }

  if(soluzaklik>=20 && ortauzaklik>=15 && saguzaklik <=20) //sol orta
  {
    Dur();
    delay(5);
    for(int i=0 ; i<=10;i++){
      ileriGit();
      delay(25);
    }
    SolaDon();
    delay(25);
    while(ortauzaklik>9)
    {
      ileriGit();
      delay(25);
      UzaklikKontroluYap();
    }
    delay(10);
  }

  if(soluzaklik<=20 && ortauzaklik>=15 && saguzaklik >=20) // orta sağ
  {
    while(saguzaklik>20)
    {
      ileriGit();
      delay(25);
      UzaklikKontroluYap();
    }
  }

  if(soluzaklik>=20 && ortauzaklik<=15 && saguzaklik >=20) // sol sağ
  {
    Dur();
    while(ortauzaklik>9)
    {
      ileriGit();
      delay(25);
      UzaklikKontroluYap();
    }
    delay(5);
    SolaDon();
    delay(10);
    for(int i=0 ; i<=10;i++){
      ileriGit();
      delay(25);
    }
  }

  if(soluzaklik<=20 && ortauzaklik<=7 && saguzaklik <=20) // çıkmaz
  {
    Dur();
    delay(5);
    GeriDon();
    delay(10);
  }

  if(soluzaklik<=20 && ortauzaklik>=7 && saguzaklik <=20) // orta
  {
    ileriGit();
  }

  if(soluzaklik>=20 && ortauzaklik<=15 && saguzaklik <=20) // sol
  {
    Dur();
    while(ortauzaklik>15)
    {
      ileriGit();
      delay(25);
      UzaklikKontroluYap();
    }
    delay(10);
    SolaDon();
    delay(10);
    while(soluzaklik>20)
    {
      ileriGit();
      delay(25);
      UzaklikKontroluYap();
    }
  }

  if(soluzaklik<=20 && ortauzaklik<=15 && saguzaklik >=20) // sağ
  {
    Dur();
    while(ortauzaklik>9)
    {
      ileriGit();
      delay(25);
      UzaklikKontroluYap();
    }
    delay(10);
    SagaDon();
    delay(10);
    for(int i=0 ; i<=15;i++){
      ileriGit();
      delay(25);
    }
 }
}

void ButonSayac() {
  if (digitalRead(BUTTON_PIN)) {
    while (digitalRead(BUTTON_PIN))
      delay(50);
    sayac++;
    Serial.println(sayac);
  }
}

void UzaklikKontroluYap() {

  soluzaklik = UzaklikHesapla(solTrigPin, solEchoPin);
  ortauzaklik = UzaklikHesapla(ortaTrigPin, ortaEchoPin);
  saguzaklik = UzaklikHesapla(sagTrigPin, sagEchoPin);

  UzakliklariYaz();
}

int UzaklikHesapla(int trig, int echo) {
  digitalWrite(sagTrigPin, LOW);
  digitalWrite(ortaTrigPin, LOW);
  digitalWrite(solTrigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  sure = pulseIn(echo, HIGH);
  uzaklik = sure / 29.1 / 2;
  return uzaklik;
}


void SagaDon() {  
  
  for(int i=0 ; i<30;i++){
    digitalWrite(sagileri, LOW); 
    digitalWrite(saggeri, HIGH); 
    digitalWrite(solileri, HIGH);
    digitalWrite(solgeri, LOW);
    delay(10);
    digitalWrite(sagileri, LOW); 
    digitalWrite(saggeri, LOW);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, LOW);
    delay(2);
  }

}

void SolaDon() { 

  for(int i=0 ; i<30;i++){
    digitalWrite(sagileri, HIGH); 
    digitalWrite(saggeri, LOW); 
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, HIGH);
    delay(10);
    digitalWrite(sagileri, LOW); 
    digitalWrite(saggeri, LOW);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, LOW);
    delay(2);
  }

  /*
  digitalWrite(sagileri, HIGH); 
  digitalWrite(saggeri, LOW); 
  digitalWrite(solileri, LOW);
  digitalWrite(solgeri, HIGH);
  delay(300);
  digitalWrite(sagileri, LOW); 
  digitalWrite(saggeri, LOW);
  digitalWrite(solileri, LOW);
  digitalWrite(solgeri, LOW);
  delay(5);*/
}


void ileriGit() {
  if( UzaklikHesapla(solTrigPin, solEchoPin) <= 6){    
    digitalWrite(solileri, HIGH);
    digitalWrite(solgeri, LOW);
    digitalWrite(sagileri, HIGH);
    digitalWrite(saggeri, LOW);
    delay(1);
    digitalWrite(solileri, HIGH);
    digitalWrite(solgeri, LOW);
    digitalWrite(sagileri, LOW);
    digitalWrite(saggeri, LOW);
    delay(2);
    return;
  }

  if( UzaklikHesapla(sagTrigPin, sagEchoPin)<=6){
    digitalWrite(solileri, HIGH);
    digitalWrite(solgeri, LOW);
    digitalWrite(sagileri, HIGH);
    digitalWrite(saggeri, LOW);
    delay(1);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, LOW);
    digitalWrite(sagileri, HIGH);
    digitalWrite(saggeri, LOW);
    delay(2);
    return;
  }
  
    digitalWrite(solileri, HIGH);
    digitalWrite(solgeri, LOW);
    digitalWrite(sagileri, HIGH);
    digitalWrite(saggeri, LOW);
    delay(25);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, LOW);
    digitalWrite(sagileri, LOW);
    digitalWrite(saggeri, LOW);
    delay(2);
}

void Dur() {
  /* Tüm motorlar kitlenerek Durma sağlanıyor */
  digitalWrite(sagileri, HIGH);
  digitalWrite(saggeri, HIGH);
  digitalWrite(solileri, HIGH);
  digitalWrite(solgeri, HIGH);
}

void GeriDon(){
  
  for(int i=0 ; i<30;i++){
    digitalWrite(sagileri, HIGH);
    digitalWrite(saggeri, LOW);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, HIGH); 
    delay(20);
    digitalWrite(sagileri, LOW);
    digitalWrite(saggeri, LOW);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, LOW);
    delay(2);
    }
  /*
    digitalWrite(sagileri, LOW); 
    digitalWrite(saggeri, HIGH);
    digitalWrite(solileri, HIGH);
    digitalWrite(solgeri, LOW);
    delay(600);
    digitalWrite(sagileri, LOW); 
    digitalWrite(saggeri, LOW);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, LOW);
    delay(1);
   while(ortauzaklik < soluzaklik || ortauzaklik < saguzaklik || ortauzaklik<50)
  {
    UzaklikKontroluYap();

    digitalWrite(sagileri, HIGH);
    digitalWrite(saggeri, LOW);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, HIGH); 
    delay(25);
    digitalWrite(sagileri, LOW);
    digitalWrite(saggeri, LOW);
    digitalWrite(solileri, LOW);
    digitalWrite(solgeri, LOW);
    delay(2);
  }
*/
}

void UzakliklariYaz()
{
  Serial.println("+++++++++++++");
  Serial.println(soluzaklik);
  Serial.println(ortauzaklik);
  Serial.println(saguzaklik);  
  Serial.println("+++++++++++++");
}

