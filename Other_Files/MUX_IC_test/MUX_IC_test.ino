//Este código foi desemvolvido para sistematizar a verificação
//Do funcionamento dos CI's 4053 utilizados na multiplexagem do sinal hdmi
//o seu funcionamento é avaliado como: 0 sem erros ou -1 com erros, 
//realizado por Bernardo Penela 

#define nE 12         //id do pin do enable a low
#define s1 6          //id do pin do switch
#define s2 7          //id do pin do switch
#define s3 8          //id do pin do switch

#define x1 3          //id do pin do mutex
#define y10 5         //id dos pins do lado do desmnutex
#define y11 4

#define x2 2          //id do pin do mutex
#define y20 1         //id dos pins do lado do desmnutex
#define y21 0

#define x3 10          //id do pin do mutex
#define y30 11         //id dos pins do lado do desmnutex
#define y31 9

#define nTestes 100

int a;    //variável temporária que guarda output
int b;    //variável temporária que guarda input
int i1;   // contadores
int i2;
int output;

void setup() {
  // put your setup code here, to run once:

  pinMode(nE, OUTPUT);
  digitalWrite(nE, LOW);

  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);

  Serial.begin(9600);

  //Teste do mutex 1

  pinMode(y10, INPUT);
  pinMode(y11, INPUT);
  pinMode(x1, OUTPUT);

  //Teste do switch 0

  Serial.print("Teste Mux 1|switch 0 = ");

  digitalWrite(s1, LOW);

  for(i2 = 0, i1 = 0;i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(x1,a);
    b = digitalRead(y10);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }

 //Teste do switch 1

  Serial.print("Teste Mux 1|switch 0 = ");
  
  digitalWrite(s1, 1);

  for(i2 = 0, i1 = 0;i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(x1,a);
    b = digitalRead(y11);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }

//Teste do demutex 1

  pinMode(y10, OUTPUT);
  pinMode(y11, OUTPUT);
  pinMode(x1, INPUT);

  //Teste do switch 0

  Serial.print("Teste deMux 1|switch 0 = ");

  digitalWrite(s1, LOW);

  for(i2 = 0, i1 = 0;i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(y10,a);
    b = digitalRead(x1);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }
  //Teste do switch 1

  Serial.print("Teste deMux 1|switch 1 = ");

  digitalWrite(s1, HIGH);

  for(i2 = 0, i1 = 0;i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(y11,a);
    b = digitalRead(x1);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }

  //Teste do mutex 2

  pinMode(y20, INPUT);
  pinMode(y21, INPUT);
  pinMode(x2, OUTPUT);

  //Teste do switch 0

  Serial.print("Teste Mux 2|switch 0 = ");

  digitalWrite(s2, LOW);

  for(i2 = 0, i1 = 0;i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(x2,a);
    b = digitalRead(y20);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print(i1);
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }

 //Teste do switch 1

  Serial.print("Teste Mux 2|switch 1 = ");
  
  digitalWrite(s2, 1);

  for(i2 = 0, i1 = 0;i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(x2,a);
    b = digitalRead(y21);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }

//Teste do demutex 2

  pinMode(y20, OUTPUT);
  pinMode(y21, OUTPUT);
  pinMode(x2, INPUT);

  //Teste do switch 0

  Serial.print("Teste deMux 2|switch 0 = ");

  digitalWrite(s2, LOW);

  for(i2 = 0, i1 = 0;i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(y20,a);
    b = digitalRead(x2);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print(i1);
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }
  //Teste do switch 1

  Serial.print("Teste deMux 2|switch 1 = ");

  digitalWrite(s2, HIGH);

  for(i2 = 0, i1 = 0; i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(y21,a);
    b = digitalRead(x2);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print(i1);
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }
  //Teste do mutex 3

  pinMode(y30, INPUT);
  pinMode(y31, INPUT);
  pinMode(x3, OUTPUT);

  //Teste do switch 0

  Serial.print("Teste Mux 3|switch 0 = ");

  digitalWrite(s3, LOW);

  for(i2 = 0, i1 = 0;i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(x3,a);
    b = digitalRead(y30);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }

 //Teste do switch 1

  Serial.print("Teste Mux 3|switch 1 = ");
  
  digitalWrite(s3, 1);

  for(i2 = 0, i1 = 0;i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(x3,a);
    b = digitalRead(y31);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }

//Teste do demutex 3

  pinMode(y30, OUTPUT);
  pinMode(y31, OUTPUT);
  pinMode(x3, INPUT);

  //Teste do switch 0

  Serial.print("Teste deMux 3|switch 0 = ");

  digitalWrite(s3, LOW);

  for(i2 = 0, i1 = 0;i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(y30,a);
    b = digitalRead(x3);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }
  //Teste do switch 1

  Serial.print("Teste deMux 3|switch 1 = ");

  digitalWrite(s3, HIGH);

  for(i2 = 0, i1 = 0; i2 < nTestes; i2++) {
    a = floor(random(2));
    digitalWrite(y31,a);
    b = digitalRead(x3);
    
    if(a != b){
      i1++;
    }

  }

  if (i1!=0){
          Serial.print("-1\n");
  }else{
          Serial.print("0\n");

  }  
}

void loop(){

}
