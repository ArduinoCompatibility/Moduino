# Moduino

## Moduino 라이브러리 함수 설명
init() : 아두이노 환경에 필요한 설정 및 초기화가 이루어지는 함수입니다.<br/>
FindID() : 연결된 모듈 전체에 모듈 정보 송신 요청을 보냅니다.
RequestProperyt(Module*) : 연결된 모듈의 신호 출력 활성화 요청을 보냅니다.<br/>
ReceiveProcess() : 모듈 신호 수신 처리 함수입니다.<br/>

## 사용 가능 모듈 목록 및 모듈별 호출가능 함수
* LED<br/>
setRGB(red,green,blue) : RGB(0~100)의 값을 출력하도록 요청합니다.<br/>

* 다이얼<br/>
getDegree() : 다이얼 모듈 회전각(0~100)에 대한 정보를 반환받습니다.<br/>

* 버튼<br/>
getClick() : 버튼 클릭 여부(0 or 100) 에 대한 정보를 반환받습니다.<br/>

## 실행 순서
1. 연결한 모듈의 정보를 파악하기 위해 setup()에서 FindID()를 호출 및 업로드 후 Serial Monitor를 이용하여 모듈들의 ID를 확인합니다.<br/>

2. 전역 변수를 사용하여 모듈별 객체 포인터를 선언 후 void setup()에서 FindID addModule(ID)를 호출하여 모듈리스트에 추가 및 객체 포인터에 저장합니다.<br/>

3. 입력모듈이 있으면 setup()에 RequestProperty(Module*)를 호출하여 입력 수신을 활성화합니다.<br/>

4. void loop()에 코드를 작성 및 아두이노에 업로드하여 실행합니다.<br/>

## 주의할 점
1. void loop()에서 반드시 ReceiveProcess()를 포함하여야 하며 이를 지울 시 입력 모듈 및 FindID()가 실행되지 않습니다.<br/>

2. void loop()의 첫 문장은 가급적 ReceiveProcess()가 되도록 합니다.<br/>

3. setup()의 첫 문장은 반드시 modi.init()이 되도록 합니다.<br/>

4. FindID() 사용 시 가급적 setup()의 마지막에 적어주도록 합니다.<br/>

5. delay() 사용 시 코드가 정상적으로 실행되지 않습니다.<br/>

## 만든이
우성윤(eereer006@hotmail.com)<br/>
유민지(upi907@naver.com)<br/>
김수영(serena0923@naver.com)<br/>
2018.08.24<br/>