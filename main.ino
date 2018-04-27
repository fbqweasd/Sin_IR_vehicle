#include<Servo.h>//서보모터 헤더 파일
#include <IRremote.h>//적외선 헤더 파일
//#include<SoftwareSerial.h> //시리얼 톨신 라이브러리(블루투스)해더파일

decode_results results;                     //수신결과가 저장됩니다.

int RECV_PIN  =A0;                            //IR Receiver로 수신한 값을 A0번 핀으로 받습니다.
int servoPin=9;//서보모터 제어
Servo servo;
int Move=5;//모터 제어

//리모컨 앞뒤좌우 적외선 신호값
int w=7650;
int a=32130;
int s=15810;
int d=23970;
int FFF=0xFFFFFFFF; 

int c=4; //정방향 역방향 조절
int set_0=90;  //서보모터 영점 값

int m_move=1; //적외선 신호를 저장을 하는 함수
int speed_fmove=1000;   //전진 속도
int speed_bmove=700;    //후진 속도
int angle=set_0;        //초깃 서보 모터의 값을 영점 조절함

//SoftwareSerial Blue(B_Tx,B_Rx);
IRrecv irrecv(RECV_PIN);                     //IR Receiver를 선언합니다.

void setup() {
  servo.attach(servoPin);     //서보모터 
  Serial.begin(9600);   //시리얼 포트 개방
  irrecv.enableIRIn();                        //IR Receiver enable
  pinMode(Move,OUTPUT);     //앞뒤 모터 핀
  servo.write(set_0);       //서보모터 초깃값으로 설정
  pinMode(4,OUTPUT);        //앞뒤 모터 정방향 역방향으로 결정하는 포트
}

void loop() {  
  //Blue_Serial();  //블루투스 신호를 받는 함수 
  move_f();       //움직이는 함수
}

void move_f()  //움직이는 함수 & 적외선 신호를 수신
{
    if(irrecv.decode(&results)){                //입력받은 값이 있을 경우에 수행
    if(results.value != FFF)
    {
      m_move=results.value; //적외선 값을 받아옴
      spen(); //회전
      move_m(); //앞뒤 움직임
    }
    Serial.println(m_move); // 무슨 값이 들어 있는지를 Serial print
    irrecv.resume();                          //다음 값을 받기위해 resume
  }

void spen()  //서보모터 회전
{
  if(m_move == d)   //오른쪽으로 회전
  {
   // Serial.println("d회전");
    Serial.println(angle);
    angle=set_0+35;
      Serial.println(angle);
     servo.write(angle);
  }
 else if(m_move == a)  //왼쪽으로 회전
  {
    // Serial.println("a회전  ");
     Serial.println(angle);
      angle=set_0-35;
        servo.write(angle);
    }
}

void move_m()  //앞뒤 이동
{
      if(m_move == s){
         digitalWrite(c,HIGH);
      //  Serial.println("후진");
        analogWrite(Move,speed_bmove);
        }
     else if(m_move == w )
     {
        digitalWrite(c,LOW);
     //   Serial.println("전진");
        analogWrite(Move,speed_fmove);
     }
     else if(m_move == a || m_move== d)
     {
      
     }
     else //이상한 값이 들어오면 초기화
     {
      analogWrite(Move,0);
      servo.write(set_0);
      angle=set_0;
     }

}
/*
void Blue_Serial()  //블루투스 신호 받는 함수
{
  if(Blue.available()) //블루투스의 값이 들어 올때
  {   
    B_data=Blue.read();   //B_data에 값을 저장을 하고 
    Serial.print("블루투스 값: ");
    Serial.println(B_data);   //시리얼 모니터로 출력
   }
}
*/

