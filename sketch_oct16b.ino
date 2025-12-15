
#include "stack.h"
#include "solver.h"
#include <LiquidCrystal.h>
#include <IRremote.h>





const int rs = A3, en = A5, d4 = A9, d5 = A10, d6 = A11, d7 = A12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int Lcm = 15;
const int Lrm = 2;

const int RECV_PIN = 7;

void setup() {
  pinMode(A14,OUTPUT);
  pinMode(A13,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A1,OUTPUT);
  digitalWrite(A14,LOW); 
  digitalWrite(A13,HIGH); 
  digitalWrite(A4,LOW); 
  digitalWrite(A0,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A1,HIGH);
  lcd.begin(Lcm, Lrm);
  lcd.setCursor(0, 1); 
  delay(2000); //Wait for display to show info
  lcd.clear();
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Ok");

}

int Lc = 0;
int Lr = 0;


size_t size = 100;
stack<char> input(size);
stack<char> output(size);

void set_position(const int&, const int&);
char command_to_char(const int&);
void Display(const char&);
void solve(char*, size_t&);


void loop() {
  
  if(IrReceiver.decode()){

    if ((IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) == 0){
      
      const int command = IrReceiver.decodedIRData.command;
      const char command_char = command_to_char(command);

      if(command_char == 'C'){
        lcd.clear();
        set_position(0, 0);
        input.clear();
        output.clear();
      } else if(command_char == '=') {
        lcd.clear();
        set_position(0, 0);
        solve(input, output);

        stack<char> expr(100);
        while(!output.empty()) {
          expr.push(output.top());
          output.pop();
        };

        stack<int> num(2);

        while(!expr.empty()) {
          if(isdigit(expr.top())) {
            num.push(expr.top()-'0');

            Serial.println(expr.top()-'0');
          } else if(expr.top()=='+') {
            int num1 = num.top(); num.pop();
           

            int num2 = num.top(); num.pop();

            num.push(num1+num2);
      
          } else if(expr.top()=='-') {
            int num1 = num.top(); num.pop();
            int num2 = num.top(); num.pop();
            num.push(num1-num2);
          } else if(expr.top()=='*') {
            int num1 = num.top(); num.pop();
            int num2 = num.top(); num.pop();
            num.push(num1*num2);
          } else if(expr.top()=='/') {
            int num1 = num.top(); num.pop();
            int num2 = num.top(); num.pop();
            num.push(num1/num2);
          };
        
          expr.pop();
        };

        

        char buffer[10]="0000000000";
        itoa(num.top(), buffer, 10);
        
        for(int i = 0; i < 10; ++i){
          if(buffer[i]=='\0') {break;}
          Display(buffer[i]);
          input.push(buffer[i]);
          
        };


      } else if (command_char != 'n') {
        Display(command_char);
        input.push(command_char);
      };
    };

    IrReceiver.resume();
  }
size_t i = 0;

};



void set_position(const int& row, const int& col) {
  Lr = row; Lc = col;
  lcd.setCursor(col, row);
}

char command_to_char(const int& command) {

  switch(command) {
    case 0x45: return '1';
    case 0x46: return '2';
    case 0x47: return '3';
    case 0x44: return '4';
    case 0x40: return '5';
    case 0x43: return '6';
    case 0x7: return '7';
    case 0x15: return '8';
    case 0x9: return '9';
    case 0x19: return '0';
    case 0x16: return '*';
    case 0xD: return '/';
    case 0x1C: return '=';
    case 0x18: return '+';
    case 0x52: return '-';
    case 0x8: return '.';
    case 0x5A: return 'C';
    default:
      return 'n';
  };
};

//1 = 0x45
//2 = 0x46
//3 = 0x47
//4 = 0x44
//5 = 0x40
//6 = 0x43
//7 = 0x7
//8 = 0x15
//9 = 0x9
//0 = 0x19
//* = 0x16
//# = 0xD
//ok = 0x1C
//w = 0x18
//s = 0x52
//a = 0x8
//d = 0x5A

void Display(const char& c){

  if(Lc > Lcm){ set_position(++Lr, 0); }

  if(Lr == Lrm){ lcd.clear(); set_position(0, 0);};

  lcd.setCursor(Lc++, Lr);

  lcd.print(c); 

}

