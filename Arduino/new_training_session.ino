//version13：设计两种变频cue，每种20次，频率分别为2kHz 到10kHz之间升高和降低。每次cue之间的时间间隔随机在10-30秒。shock在cue中间or结束前

long randNumber;
long randtime;
int buttonpin1 = 3;   //声音引脚-
int buttonpin2 = 10;  //声音引脚+
int buttonpin3 = 4;   //声音cue电刺激引脚：正极(数字接口)
int analogpin1 = 8;    //用来输出marker的引脚(数字接口)  HIGH代表高频声音cue的时间段；LOW代表没有高频声音cue的时间段
int analogpin2 = 2;     //HIGH代表有低频声音cue的时间段，LOW代表没有低频声音cue的时间段
int inputpin1 = 7;    //接收程序启动信号的引脚
int inputpin2 = 12;    //接收首次电击信号的引脚
int randomcount = 40;   //随机数生成的范围
int trial1 = 1; //统计有电击trial的次数
int trial2 = 1; //统计无电击trial的次数


//定义声音频率变化的范围
#define UP_MIN_FREQUENCY 1000
#define UP_MAX_FREQUENCY 3000
#define DOWN_MIN_FREQUENCY 6000
#define DOWN_MAX_FREQUENCY 8000
#define cue_time 2000

// 定义随机序列参数
const int totalCount = 14;     // 总次数（必须是偶数）
const int maxConsecutive = 2;  // 最大连续次数
int sequence[totalCount];      // 存储生成的序列

// 验证序列是否符合要求
bool validateSequence() {
  int countA = 0;             // A的总数
  int countB = 0;             // B的总数
  int currentConsecA = 0;     // 当前连续A的次数
  int currentConsecB = 0;     // 当前连续B的次数

  for (int i = 0; i < totalCount; i++) {
    if (sequence[i] == 1) {   // 条件A
      countA++;
      currentConsecA++;
      currentConsecB = 0;
      if (currentConsecA > maxConsecutive) {
        return false;
      }
    } else {                  // 条件B
      countB++;
      currentConsecB++;
      currentConsecA = 0;
      if (currentConsecB > maxConsecutive) {
        return false;
      }
    }
  }

  // 检查A和B的数量是否相等
  return (countA == countB);
}

// 随机序列生成函数
void generateSequence() {
  bool isValid = false;
  
  while (!isValid) {
    int countA = 0;           // 记录条件A的出现次数
    int countB = 0;           // 记录条件B的出现次数
    int consecutiveA = 0;     // 连续出现的A的次数
    int consecutiveB = 0;     // 连续出现的B的次数

    for (int i = 0; i < totalCount; i++) {
      bool chooseA;           // 当前选择A还是B
      
      // 确定选择逻辑
      if (countA >= totalCount / 2) {
        chooseA = false;      // A次数已达上限，选B
      } else if (countB >= totalCount / 2) {
        chooseA = true;       // B次数已达上限，选A
      } else if (consecutiveA >= maxConsecutive) {
        chooseA = false;      // A连续达到上限，选B
      } else if (consecutiveB >= maxConsecutive) {
        chooseA = true;       // B连续达到上限，选A
      } else {
        chooseA = random(2) == 0; // 随机选择
      }

      // 更新序列和计数器
      if (chooseA) {
        sequence[i] = 1;      // 条件A
        countA++;
        consecutiveA++;
        consecutiveB = 0;
      } else {
        sequence[i] = 0;      // 条件B
        countB++;
        consecutiveB++;
        consecutiveA = 0;
      }
    }
    
    // 验证生成的序列
    isValid = validateSequence();
  }
}

// 打印序列函数
void printSequence() {
  Serial.print("Valid Sequence: ");
  for (int i = 0; i < totalCount; i++) {
    Serial.print(sequence[i]);
    Serial.print(" ");
  }
  Serial.println();
}





//定义变频的声音函数
void Down_Frequency(){
  long start_time;
  long time;
  int restart_label = 0;
  unsigned long frequency;
  if(restart_label == 0){
    start_time = millis();
    restart_label = 1;
  }
  time = millis() - start_time;
  while(time <= cue_time){
    frequency = DOWN_MAX_FREQUENCY - time; 
    tone(buttonpin2, frequency);
    time = millis() - start_time;
  }
  noTone(buttonpin2);
  restart_label = 0;
}

void Up_Frequency(){
  long start_time;
  long time;
  int restart_label = 0;
  unsigned long frequency;
  if(restart_label == 0){
    start_time = millis();
    restart_label = 1;
  }
  time = millis() - start_time;
  while(time <= cue_time){
    frequency = time + UP_MIN_FREQUENCY; 
    tone(buttonpin2, frequency);
    time = millis() - start_time;
  }
  noTone(buttonpin2);
  restart_label = 0;
}


void setup(){
  Serial.begin(9600);   //用于测试输出结果
  randomSeed(analogRead(A0)); 
  pinMode(buttonpin1, OUTPUT);
  digitalWrite(buttonpin1, HIGH);
  pinMode(buttonpin3, OUTPUT);
  pinMode(analogpin1, OUTPUT);
  pinMode(analogpin2, OUTPUT);
  pinMode(inputpin1,INPUT);
  pinMode(inputpin2,INPUT);
  //将引脚A0放空，每次程序启动时所读取的数值都是不同的。
  //这么做可以产生真正的随机种子值，从而产生随机数值。
}



//digitalRead(inputpin) == HIGH
void loop(){
  //首次电刺激:session1有， session2 & session3 没有
  if(digitalRead(inputpin2) == HIGH){
    digitalWrite(buttonpin3, HIGH);  //给与一定时间的电刺激
    delay(2000);  //这个时间是控制电刺激持续的时间
    digitalWrite(buttonpin3,LOW);  //恢复电击器低电平
  }
  //如果引脚7为高电平则启动下面的程序digitalRead(inputpin1) == HIGH
  if(digitalRead(inputpin1) == HIGH){
    int i;   //循环变量，控制trial总数的循环
    for(i = 0; i<totalCount; i++){
    if(i == 0){
      // 打印结果
      generateSequence();
      printSequence();
    }
    randtime = random(30,50);
     //为了控制两种trial的次数相同，在if条件中加一个trial变量记录其次数
    if(sequence[i] == 1){
      Serial.println("tone1的次数:");  //便于查看输出结果
      Serial.println(trial1);
      Serial.println("间隔时间:");
      Serial.println(randtime);
      digitalWrite(analogpin1,HIGH);   //输出一个高电平：表示声音cue的开始
      Up_Frequency();   //升频函数：一个函数执行2秒的变频声音
      Up_Frequency();
      Up_Frequency();
      Up_Frequency();
      Up_Frequency();
      Up_Frequency();
      Up_Frequency();
      Up_Frequency();
      Up_Frequency();
      Up_Frequency();
      digitalWrite(analogpin1,LOW);    //输出一个低电平：表示声音cue的结束
      delay(randtime*1000);     //每两个trial之间的间隔时间
      trial1 = trial1 + 1;
      }
    if(sequence[i] == 0){
      Serial.println("tone2的次数:");  
      Serial.println(trial2);
      Serial.println("间隔时间:");
      Serial.println(randtime);
      digitalWrite(analogpin2,HIGH);   //输出一个高电平信号：表示声音cue的开始
      digitalWrite(buttonpin3, LOW);  //不给与电刺激，保证处于一个低电平状态
      Down_Frequency();     //降频函数：执行时间2秒
      Down_Frequency();
      Down_Frequency();
      Down_Frequency();
      Down_Frequency();
      digitalWrite(buttonpin3, HIGH);  //给电刺激：给与一定时间的电刺激
      Down_Frequency();
      digitalWrite(buttonpin3, LOW);   //恢复低电平状态，结束电刺激
      Down_Frequency();
      Down_Frequency();
      Down_Frequency();
      Down_Frequency();
      digitalWrite(analogpin2,LOW);  //输出一个低电压信号：表示声音cue的结束
      delay(randtime*1000);   //保证两种trail的总时间一致
      trial2 = trial2 + 1;
      }
    }
    Serial.println("All trials end!");
    Serial.println(i);
    delay(180000);    //一系列trial结束后间隔3min，可以选择停止，也可以选择合适的间隔时间进行下一次trial
    Serial.println("3 min later!");
  }
  else{
    delay(1);
  }
}