# Autonomous-Ships-Project
⦁ 관광지에 있어 조경관리는 하나의 관심거리로 자리를 잡아왔습니다. 많은 금액을 조경관리에 쏟아붓지만 많은 문제점을 바라볼 수 있습니다.  
그 문제 중 저희 팀은 인력 문제에 초점을 두고 생각해 봤습니다.  

넓은 관광지일수록 많은 인력을 필요로 하게 되고 지면 위가 아닌 수면의 조경을 관리하려면 장비가 필요하고 인력이 커버할 수 있는 한계가 있습니다.  

이에 한 가지 솔루션을 이 프로젝트를 통하여 제안합니다.  

⦁ 아두이노를 이용하여 수면 위를 자율주행하는 드론  
⦁ BLCD 브러시리스 모터 사용, 적외선 거리감지 센서를 이용하여 장애물 회피 시도  
# 사용된 센서
⊙ 적외선 거리감지 센서  
⊙ ESC 변압기(모터 제어에 필요)  
⊙ BLDC(브러시리스) 모터  
⊙ L293D 모터쉴드  
⊙ 아두이노 2560 MEGA  
# 코드

 
개선해 나갈 점
>> 아두이노로 자율주행을 구현하기엔 많은 제약이 보임

>> 적외선 거리감지 센서는 정면의 장애물은 잘 감지하지만 정면만 감지하는 것이 단점 (사방의 장애물을 감지에 적합하지 않음)
## 1. 컨셉 디자인

<img src = "https://user-images.githubusercontent.com/48241432/121632402-e2574f80-cabb-11eb-9e83-293e871f026d.jpg" width="48%" height="height 48%"> <img src = "https://user-images.githubusercontent.com/48241432/121638358-cce72300-cac5-11eb-8d39-43bdb4322389.jpg" width="48%" height="height 48%">

## 2. 선박 모델링

<img src = "https://user-images.githubusercontent.com/48241432/121631891-e8006580-caba-11eb-81ce-842ff6e8f27a.jpg" width="50%" height="height 50%">

## 3. 자율주행 선박 회로도

<img src = "https://user-images.githubusercontent.com/48241432/121631779-b38ca980-caba-11eb-9404-4c04b5fae526.png" width="50%" height="height 50%">
