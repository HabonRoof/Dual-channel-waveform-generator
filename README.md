# 基於AD9833之雙通道直接數位合成波型產生器

## 簡介  

本專案使用AD9833直接數位信號合成器(Direct Digital Synthesizer)，利用數位方式產生任意波型與頻率。  
控制端使用與Arduino UNO相同之Atmega328P微處理器，顯示器使用128*64藍底白字LCD顯示器。  
使用方法:
首先透過LCD螢幕設定各通道之波型、頻率、相位等等參數，透過微處理器設定參數，再由AD9833產生對應之波型訊號。  
此訊號會再透過LM318 高轉動率(Slew Rate)運算放大器將電壓放大至+12V~-12V之振幅。  
此外，板載之+12、-12、5V電源使用線性穩壓器做為電源供應，提供乾淨無雜訊之直流電源，以避免市電雜訊干擾波型輸出。  

## 波型展示
最大電壓輸出  

最小電壓輸出  

最高頻率輸出  
![12.5 MHz 輸出](https://github.com/HabonRoof/Dual-channel-waveform-generator/blob/master/Image/969313.jpg)
最低頻率輸出  

正弦波  
![6kHz 正弦波輸出](https://github.com/HabonRoof/Dual-channel-waveform-generator/blob/master/Image/969322.jpg)
方波
![1kHz 方波輸出](https://github.com/HabonRoof/Dual-channel-waveform-generator/blob/master/Image/969316.jpg)
三角波
![1kHz 三角波輸出](https://github.com/HabonRoof/Dual-channel-waveform-generator/blob/master/Image/969315.jpg)
主選單畫面
![通道輸出狀態以及主選單](https://github.com/HabonRoof/Dual-channel-waveform-generator/blob/master/Image/969321.jpg)
通道1 設定選擇畫面
![Ch1 設定](https://github.com/HabonRoof/Dual-channel-waveform-generator/blob/master/Image/969318.jpg)
波型選擇畫面
![CH1波型選擇](https://github.com/HabonRoof/Dual-channel-waveform-generator/blob/master/Image/969317.jpg)
頻率設定畫面
![Ch1頻率設定(https://github.com/HabonRoof/Dual-channel-waveform-generator/blob/master/Image/969319.jpg)
頻率設定畫面-2
![Ch1頻率設定畫面-2](https://github.com/HabonRoof/Dual-channel-waveform-generator/blob/master/Image/969320.jpg)


##材料表
AD9833 DDS Module x2   
Atmega328P x1  
LM318 運算放大器 x2  
12W 110/220V轉12Vac 變壓器 x1  
10k Ohm 可變電阻 x2  
100k Ohm 可變電阻 x2  
旋轉編碼器 x1  
開關 x2  
專案盒 x1  
電容器 x6  

## 硬體介紹
###AD9833 DDS 訊號產生器  
[維基百科-直接數位訊號合成](https://zh.wikipedia.org/wiki/%E7%9B%B4%E6%8E%A5%E6%95%B0%E5%AD%97%E5%90%88%E6%88%90)  
[Digikey-直接數位合成器-基本知識](https://www.digikey.tw/zh/articles/the-basics-of-direct-digital-synthesizers-ddss)  
直接數位訊號合成器基本原理就是使用內建的數位訊號表，紀錄不同訊號的波型振福， 
晶片讀取波型振福後，利用自身的類比數位訊號轉換器將資料轉換成實際電壓輸出，進而模擬出連續的類比訊號。  
然而，受限於最大系統時脈頻率，最高的模擬波型輸出頻率只有系統時脈頻率的1/2，此為奈奎氏頻率的限制，  
但可以更簡單的理解成在方波的情況下，波型有兩種狀況:最大與最小，而假設系統時脈頻率為fs，輸出頻率最大也只能到1/2 fs。  
DDS雖然可以透過查表產生不同波型，但其本質仍然是使用方波座數位訊號合成，因此在輸出波型中會含有系統時脈的諧波成分，  
要解決此問題需要在輸出端放置一低通濾波器將高頻諧波截去。此濾波器截止頻率需設定稍高於最大輸出頻率，即1/2 fs。
更詳細的原理可以參考上方超連結。  

###LM318 運算放大器  
電子電路中，運算放大器為常見的使用零件，但在基礎實習應用或比較器應用中，較不重視轉動率(Slew Rate)這項參數。  
此參數是評價運算放大器速度的重要指標，其定義為: 單位時間內可變化的電壓大小，單位為 V/uS。
在本專案一開始，使用LM358 作為訊號放大器，但其轉動率只有0.3V/uS，其較慢的轉動率使的DDS產生高頻訊號時，無法放大輸入訊號，導致輸出訊號震幅降低。  
後來改使用LM318訊號放大器後，其轉動率為70V/uS，此特性雖不足以滿足我們最高頻率12.5MHz，最大峰對峰值24V之設計，但可計算出在1MHz輸出下，電壓震幅可達7V之特性。  
這已經滿足大部分的應用需求了。  

###Atmega 328P 8位元微處理器  
大家熟悉的Arduino UNO就是使用這顆微控制器，本專案使用Atmega328P最精簡電路，並透過USB-TTL 燒錄器將程式碼燒錄進晶片中。  
Atmega最精簡電路只需要16MHz石英晶體震盪器、2x22pF陶瓷電容器、按鈕開關以及10k Ohm電阻即可建構。  
燒錄器可選擇任意USB5轉TTL串列埠訊號轉換器，在電腦端安裝好轉換器的驅動程式後，使用Arduino IDE燒錄時，當狀態是列顯示"上傳中" 時，按下重製按鈕便可將程式碼上傳至微處理機中。

###12864LCD液晶顯示器  
此液晶顯示器與市面上常見之128X64液晶顯示器稍微不同，因為是從對岸採購的，所以其函式庫

## 軟體介紹
firmware_v1.0 .ino  
第1.0版本波型產生器主要程式，

lcd_screens.ino  
液晶顯示器特定頁面  

lcdUI.h  
LCD目錄子函式，包含主目錄、通道設定、波型選擇、頻率選擇、相位選擇。  
此項目專攻coding的人看到會發瘋，因為我亂用class級別 QQ  
照理說可以再把這部分簡化，或者直接用子程式取代即可。  

## 已知問題
1. 此波型產生器之最高頻率為12.5MHz(方波，系統頻率為24MHz時)，受限於V1.0版本資料型態以及變數設置，最大只有10MHz，仍待改進。
2. 選單主畫面缺乏目前通道訊號狀態
3. 線性穩壓器溫度需要量測
4. V1.0版尚未支援波型相位設定
5. 實際輸出與設定值似乎有誤差，檢查lcdSetFrequency涵式

##改進目標
1. 功率消耗過高，浪費在線性穩壓器上
2. 硬體忘記留韌體燒錄孔 QwQ 每次都要拆開更新韌體
