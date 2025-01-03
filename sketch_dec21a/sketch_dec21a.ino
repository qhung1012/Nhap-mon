#include <LiquidCrystal.h>
#include <Servo.h>

int angle1;
int angle2;
int angle3;

typedef struct{
  char name[10];
  int check; //bằng 0 nếu ko có xe đỗ và ngược lại
}p_lot; //kieu du lieu gom cac ô đỗ xe
p_lot p[3]={{"a1",0},{"a2",0},{"a3",0}};// mảng gồm các chỗ đỗ xe

class usonic_ss{
  public:
  Servo sv; // servo ứng với cảm biến đó
  int id_p_lot[3];// mảng chứa chỉ số của mảng p[] tức là những ô mà cảm biến đấy sẽ detect
  int echopin;
  int trigpin;
  usonic_ss(): id_p_lot({0,1,2}), echopin(7), trigpin(8) {} // không truyền tham số thì mặc định là như này
  usonic_ss(int id[],int trig, int echo): echopin(echo),trigpin(trig) {
    for(int i=0;i<3;i++){
      id_p_lot[i]=id[i];
    }
  }
  ~usonic_ss(){}
  void detect(int x); //check xem xe đấy đỗ chx (khoảng cách <= bn đấy thì p[x].check=1 và ngược lại)
  void rotate(); //quay 3 góc và detect() sử dụng hàm detect ở trên 
};

void usonic_ss:: rotate(); //quay 3 góc và detect() sử dụng hàm detect ở trên

void usonic_ss::detect();

void displayonlcd(p_lot pl[]);

usonic_ss ss; //cam bien tên u1 (vì mình có một cảm biến nên khao báo 1 biến thôi nhiều thì sẽ là mảng)

void setup() {
  ss.sv.attach(9); //pin cua servo ung voi u1
  pinMode(ss.echopin, OUTPUT);
  pinMode(ss.trigpin, INPUT);
}
void loop() {
  ss.rotate();
  displayonlcd(p);
}
