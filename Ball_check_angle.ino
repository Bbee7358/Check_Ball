int Ball_1;  //前
int Ball_2;  //右前前
int Ball_3;  //右前
int Ball_4;  //右前右
int Ball_5;  //右
int Ball_6;  //右後右
int Ball_7;  //右後
int Ball_8;  //右後後
int Ball_9;  //後
int Ball_10;  //左後後
int Ball_11;  //左後
int Ball_12;  //左後左
int Ball_13;  //左
int Ball_14;  //左前左
int Ball_15;  //左前
int Ball_16;  //左前前

int ir[17];  //ボールの値
uint8_t ir_8bit[17]; //ボールのデジタルがレジスタで入る
int ir_digital[17];  //ボールのデジタル値の逆の値が入る
int L = 1000;  //ボールの値を数える回数

int e = 0;  //ボールの値を比較しながら、一番大きなボールの値が入る
int c = 0;  //一番のボールの番号
float angleB = 0;  //ボールの角度

int q;

//スタートボタン
#define SWICH 52  //ピン47を「SWICH」とする

void setup() {
  Serial.begin(115200);
  Serial.println("Ball_check");
  Serial.println("");  //改行
  //IRをinputにする
  DDRC &= ~(_BV(0) | _BV(1) | _BV(2) | _BV(3) | _BV(4) | _BV(5));
  DDRD &= ~_BV(7);
  DDRG &= ~(_BV(0) | _BV(1) | _BV(2));
  DDRL &= ~(_BV(2) | _BV(3) | _BV(4) | _BV(5) | _BV(6) | _BV(7));

//  //スイッチをinput
//  pinMode(SWICH,INPUT);
}
void loop() {
  //analog値リセット
  for(int m=0; m<=16; m++)
  {
    ir[m] = 0;  //ボールの値をリセット　×16
  }
  
  for (int k=0; k<L; k++)
  {
    ir_8bit[1] = PIND & _BV(7);  //前
    ir_8bit[2] = PING & _BV(1);  //右前前
    ir_8bit[3] = PINL & _BV(7);  //右前
    ir_8bit[4] = PINL & _BV(5);  //右前右
    ir_8bit[5] = PINL & _BV(3);  //右
    ir_8bit[6] = PINL & _BV(2);  //右後右
    ir_8bit[7] = PINL & _BV(4);  //右後
    ir_8bit[8] = PINL & _BV(6);  //右後後
    ir_8bit[9] = PING & _BV(0);  //後
    ir_8bit[10] = PING & _BV(2);  //左後後
    ir_8bit[11] = PINC & _BV(0);  //左後
    ir_8bit[12] = PINC & _BV(2);  //左後左
    ir_8bit[13] = PINC & _BV(4);  //左
    ir_8bit[14] = PINC & _BV(5);  //左前左
    ir_8bit[15] = PINC & _BV(3);  //左前
    ir_8bit[16] = PINC & _BV(1);  //左前前

    for(int m=0; m<=16; m++)
    {
      if(ir_8bit[m] > 0)  //ボールの値がHIGHだったら
      {
        ir_digital[m] = 0;  //なぜ1ではなく0にするかというと、ボールセンサがボールが近くにあるほど0が出るため、近づくとボールの値が高くなるようにするため
      }
      else  //ボールの値がLOWだったら
      {
        ir_digital[m] = 1;
      };
    };

    //irの値を格納する変数にIRのセンサー値を足していく
    for(int m=0; m<=16; m++)
    {
      ir[m] += ir_digital[m];
    };
  };

  
  if(ir[1]>ir[2]){
    e = ir[1];
    c = 1;  //前
  }else{
    e = ir[2];
    c = 2;
  };
  for(int k=2; k<=16; k++)
  {
    if(ir[k] > e)
    {
      e = ir[k];
      c = k;
    };
  };
  
  if(c > 8){  //左側をむいていたら
    angleB = 22.5*(c-1) - 360;
  }else{  //右側を向いていたら
    angleB = 22.5 * (c-1);
  };

//  if(digitalRead(SWICH) == LOW)  //スイッチがオンであれば計測する
//  {
//    Serial.print(ir[5]); Serial.println(" ");
//    q = 1;
//  }else  //スイッチがオフならば
//  {
//    if(q == 1)  //スイッチがオフになった直前ならば
//    {
//      Serial.println("------------");
//      q = 0;
//    }
//  }
  Serial.print("1:"); Serial.print(ir[1]);
  Serial.print(" 2:"); Serial.print(ir[2]);
  Serial.print(" 3:"); Serial.print(ir[3]);
  Serial.print(" 4:"); Serial.print(ir[4]);
  Serial.print(" 5:"); Serial.print(ir[5]);
  Serial.print(" 6:"); Serial.print(ir[6]);
  Serial.print(" 7:"); Serial.print(ir[7]);
  Serial.print(" 8:"); Serial.print(ir[8]);
  Serial.print(" 9:"); Serial.print(ir[9]);
  Serial.print(" 10:"); Serial.print(ir[10]);
  Serial.print(" 11:"); Serial.print(ir[11]);
  Serial.print(" 12:"); Serial.print(ir[12]);
  Serial.print(" 13:"); Serial.print(ir[13]);
  Serial.print(" 14:"); Serial.print(ir[14]);
  Serial.print(" 15:"); Serial.print(ir[15]);
  Serial.print(" 16:"); Serial.println(ir[16]);
  Serial.print("  e:"); Serial.print(e);
  Serial.print(" c:"); Serial.print(c);
  Serial.print(" angleB:"); Serial.print(angleB); Serial.println("°");
}
