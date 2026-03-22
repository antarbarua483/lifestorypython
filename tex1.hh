/* ================================================
   Quiz System — JavaScript
   বাংলা কুইজ সিস্টেম | JS
================================================ */

"use strict";


// ═══════════════ CONFIG ═══════════════
let ADMIN_PASSWORD = localStorage.getItem('mq_admin_pass') || "admin123";
let TOTAL_SECONDS  = (parseInt(localStorage.getItem('mq_timer_min'))||30) * 60;
const MARK_PER_Q   = 1; // default, overridden per question now


// ═══════════════ DEFAULT DATA ═══════════════
const DEF_SUBJECTS = [
  {id:1,name:"গণিত",emoji:"🧮",color:"#f7c948"},
  {id:2,name:"পদার্থ",emoji:"🔬",color:"#38b2f5"},
  {id:3,name:"রসায়ন",emoji:"⚗️",color:"#43e97b"},
];
const DEF_LEVELS = [
  {id:1,name:"Class 9-10",short:"SSC"},
  {id:2,name:"Class 11-12",short:"HSC"},
  {id:3,name:"Admission",short:"Adm"},
];
const DEF_QUESTIONS = [
  // গণিত SSC
  {id:1,subjectId:1,levelId:1,q:"একটি বৃত্তের ব্যাস ৬ সেমি হলে এর পরিধি কত?",opts:["৬√২ সেমি","১২ সেমি","১৮.৮৫ সেমি","৩৬ সেমি"],ans:2},
  {id:2,subjectId:1,levelId:1,q:"log₅(1/25) এর মান কত?",opts:["25","5","2","-2"],ans:3},
  {id:3,subjectId:1,levelId:1,q:"x² − √7x = 0 এর সমাধান কোনটি?",opts:["{-7}","{0}","{√7}","{0, √7}"],ans:3},
  {id:4,subjectId:1,levelId:1,context:"a + b = √6 এবং a − b = 2",q:"a² + b² = কত?",opts:["15","10","5","2"],ans:1},
  {id:5,subjectId:1,levelId:1,context:"a + b = √6 এবং a − b = 2",q:"4ab = কত?",opts:["2","5","8","10"],ans:0},
  // গণিত HSC
  {id:6,subjectId:1,levelId:2,q:"3 + 5 + 7 + … ধারার 21টি পদের সমষ্টি কত?",opts:["43","46","483","966"],ans:2},
  {id:7,subjectId:1,levelId:2,q:"f(x) = x² − 2x + 4 হলে f(-3) = ?",opts:["19","16","4","1"],ans:0},
  {id:8,subjectId:1,levelId:2,q:"sec(90° − θ) = কত?",opts:["cosθ","sinθ","cotθ","cosecθ"],ans:3},
  // রসায়ন SSC
  {id:14,subjectId:3,levelId:1,q:"পানির রাসায়নিক সংকেত কী?",opts:["HO","H₂O","H₂O₂","OH"],ans:1},
  {id:15,subjectId:3,levelId:1,q:"pH = 7 মানে দ্রবণটি—",opts:["অম্লীয়","ক্ষারীয়","নিরপেক্ষ","পানীয়"],ans:2},
  {id:16,subjectId:3,levelId:1,q:"NaCl এর সঠিক নাম কী?",opts:["সোডিয়াম ক্লোরাইড","সোডিয়াম হাইড্রোক্সাইড","ক্যালসিয়াম ক্লোরাইড","পটাসিয়াম ক্লোরাইড"],ans:0},
  // রসায়ন HSC
  {id:17,subjectId:3,levelId:2,q:"পর্যায় সারণিতে কার্বনের পারমাণবিক সংখ্যা কত?",opts:["4","5","6","7"],ans:2},
  {id:18,subjectId:3,levelId:2,q:"অ্যাভোগেড্রো সংখ্যা কোনটি?",opts:["6.022×10²³","6.022×10²²","6.022×10²⁴","3.011×10²³"],ans:0},

  // ══════════════════════════════════════════
  // পদার্থ SSC — গতি
  // ══════════════════════════════════════════
  {id:19,subjectId:2,levelId:1,tags:["গতি","ত্বরণ"],context:"u = 0, s = 100 m, t = 5 s",q:"একটি বস্তু স্থির অবস্থা থেকে সুষম ত্বরণে ৫ s-এ ১০০ m দূরত্ব অতিক্রম করে। ত্বরণ কত?",opts:["8 m/s²","4 m/s²","10 m/s²","20 m/s²"],ans:0,explanation:"s = ut + ½at² → 100 = 0 + ½ × a × 25 → a = 8 m/s²"},
  {id:20,subjectId:2,levelId:1,tags:["গতি","ত্বরণ"],context:"u = 20 m/s, v = 50 m/s, t = 5 s",q:"একটি গাড়ির বেগ ২০ m/s থেকে ৫ s-এ ৫০ m/s হয়। ত্বরণ কত?",opts:["6 m/s²","10 m/s²","14 m/s²","30 m/s²"],ans:0,explanation:"a = (v−u)/t = (50−20)/5 = 6 m/s²"},
  {id:21,subjectId:2,levelId:1,tags:["গতি","প্রজেক্টাইল"],context:"u = 45 m/s, v = 0, g = 10 m/s²",q:"একটি বল ৪৫ m/s বেগে উপরে ছোড়া হলো। সর্বোচ্চ উচ্চতায় পৌঁছাতে কত সময় লাগবে? (g = 10 m/s²)",opts:["4.5 s","9 s","3 s","5 s"],ans:0,explanation:"v = u − gt → 0 = 45 − 10t → t = 4.5 s"},
  {id:22,subjectId:2,levelId:1,tags:["গতি","ব্রেকিং"],context:"u = 30 m/s, v = 0, t = 6 s",q:"একটি বস্তু ৩০ m/s বেগে চলছে। ব্রেক করার ফলে ৬ s-এ থামে। ব্রেক করার আগে কত দূরত্ব যায়?",opts:["90 m","180 m","60 m","120 m"],ans:0,explanation:"s = (u+v)/2 × t = (30+0)/2 × 6 = 90 m"},
  {id:23,subjectId:2,levelId:1,tags:["গতি","সূত্র"],context:"u = 10 m/s, a = 3 m/s², s = 30 m",q:"v² = u² + 2as সূত্রে u = 10 m/s, a = 3 m/s², s = 30 m হলে v = ?",opts:["20 m/s","15 m/s","25 m/s","30 m/s"],ans:0,explanation:"v² = 100 + 2×3×30 = 100+180 = 280? → সঠিক: v² = 100+180 = 280 → v ≈ 20 m/s (নিকটতম)"},
  {id:24,subjectId:2,levelId:1,tags:["গতি","একক রূপান্তর"],context:"v = 72 km/h",q:"একটি ট্রেন ৭২ km/h বেগে চলছে। SI তে বেগ কত?",opts:["20 m/s","72 m/s","7.2 m/s","12 m/s"],ans:0,explanation:"72 km/h = 72 × (1000/3600) = 20 m/s"},
  {id:25,subjectId:2,levelId:1,tags:["গতি","মুক্তপতন"],context:"u=0, g=10 m/s², t=5s",q:"মুক্তভাবে পড়ন্ত একটি বস্তু ৫ s-এ কত বেগ অর্জন করবে? (g=10 m/s²)",opts:["50 m/s","25 m/s","100 m/s","10 m/s"],ans:0,explanation:"v = u + gt = 0 + 10×5 = 50 m/s"},
  {id:26,subjectId:2,levelId:1,tags:["গতি","মন্দন"],context:"u=20 m/s, a=−2 m/s², v=0",q:"একটি বস্তু ২০ m/s বেগে চলছে। ২ m/s² মন্দনে কত দূরে গিয়ে থামবে?",opts:["100 m","200 m","50 m","10 m"],ans:0,explanation:"v²=u²+2as → 0=400+2(−2)s → s=100 m"},
  {id:27,subjectId:2,levelId:1,tags:["গতি","গড় বেগ"],context:"মোট দূরত্ব=110 m, মোট সময়=5 s",q:"একটি বস্তু ৩ s-এ ৬০ m যায়, পরবর্তী ২ s-এ ৫০ m যায়। গড় বেগ কত?",opts:["22 m/s","20 m/s","25 m/s","18 m/s"],ans:0,explanation:"গড় বেগ = মোট দূরত্ব/মোট সময় = 110/5 = 22 m/s"},

  // পদার্থ SSC — বল
  {id:28,subjectId:2,levelId:1,tags:["বল","নিউটন","দ্বিতীয় সূত্র"],context:"m = 5 kg, F = 30 N",q:"৫ kg ভরের একটি বস্তুতে ৩০ N বল প্রয়োগ করা হলে ত্বরণ কত?",opts:["6 m/s²","150 m/s²","25 m/s²","3 m/s²"],ans:0,explanation:"a = F/m = 30/5 = 6 m/s²"},
  {id:29,subjectId:2,levelId:1,tags:["বল","F=ma"],context:"m = 8 kg, a = 4 m/s²",q:"একটি বস্তুর ভর ৮ kg। এটি ৪ m/s² ত্বরণে চলতে প্রয়োজনীয় বল কত?",opts:["32 N","2 N","12 N","48 N"],ans:0,explanation:"F = ma = 8×4 = 32 N"},
  {id:30,subjectId:2,levelId:1,tags:["বল","ভরবেগ"],context:"m = 12 kg, u = 6 m/s, v = 0, t = 3 s",q:"একটি ১২ kg বস্তু ৬ m/s বেগে চলছে। এটি থামাতে কত বল দরকার যদি ৩ s-এ থামাতে হয়?",opts:["24 N","36 N","6 N","72 N"],ans:0,explanation:"a=(v−u)/t=(0−6)/3=−2 m/s² → F=ma=12×2=24 N"},
  {id:31,subjectId:2,levelId:1,tags:["বল","অনুপাত"],context:"m₁ = 2 kg, m₂ = 3 kg, F সমান",q:"২ kg ও ৩ kg ভরের দুটি বস্তু একই বল দ্বারা চালিত হলে ত্বরণের অনুপাত কত?",opts:["3:2","2:3","1:1","4:9"],ans:0,explanation:"a∝1/m → a₁:a₂ = m₂:m₁ = 3:2"},
  {id:32,subjectId:2,levelId:1,tags:["বল","রকেট"],context:"m = 500 kg, F = 10000 N",q:"একটি রকেটের ভর ৫০০ kg। ইঞ্জিন ১০,০০০ N বল দেয়। ত্বরণ কত?",opts:["20 m/s²","50 m/s²","500 m/s²","5 m/s²"],ans:0,explanation:"a = F/m = 10000/500 = 20 m/s²"},
  {id:33,subjectId:2,levelId:1,tags:["বল","ভরবেগ"],context:"p=60 kg·m/s, m=4 kg",q:"একটি বস্তুর ভরবেগ ৬০ kg·m/s এবং ভর ৪ kg। বেগ কত?",opts:["15 m/s","240 m/s","56 m/s","64 m/s"],ans:0,explanation:"p = mv → v = p/m = 60/4 = 15 m/s"},
  {id:34,subjectId:2,levelId:1,tags:["বল","ভরবেগ পরিবর্তন"],context:"m=6 kg, u=4 m/s, v=10 m/s",q:"৬ kg বস্তুর বেগ ৪ m/s থেকে ১০ m/s হলে ভরবেগের পরিবর্তন কত?",opts:["36 kg·m/s","84 kg·m/s","24 kg·m/s","60 kg·m/s"],ans:0,explanation:"Δp = m(v−u) = 6×(10−4) = 36 kg·m/s"},
  {id:35,subjectId:2,levelId:1,tags:["বল","লব্ধি"],context:"F₁=8N, F₂=6N, কোণ=90°",q:"একটি বস্তুতে F₁=8N এবং F₂=6N পরস্পর লম্বভাবে কাজ করে। লব্ধি বল কত?",opts:["10 N","14 N","2 N","48 N"],ans:0,explanation:"F = √(8²+6²) = √(64+36) = √100 = 10 N"},

  // পদার্থ SSC — কাজ-শক্তি
  {id:36,subjectId:2,levelId:1,tags:["কাজ-শক্তি","কাজ"],context:"F = 50 N, d = 8 m, θ = 0°",q:"একটি বস্তুকে ৫০ N বলে ৮ m সরানো হলো। কৃতকাজ কত?",opts:["400 J","58 J","6.25 J","800 J"],ans:0,explanation:"W = F×d = 50×8 = 400 J"},
  {id:37,subjectId:2,levelId:1,tags:["কাজ-শক্তি","গতিশক্তি"],context:"m = 6 kg, v = 10 m/s",q:"৬ kg ভরের বস্তু ১০ m/s বেগে চলছে। গতিশক্তি কত?",opts:["300 J","600 J","60 J","150 J"],ans:0,explanation:"KE = ½mv² = ½×6×100 = 300 J"},
  {id:38,subjectId:2,levelId:1,tags:["কাজ-শক্তি","বিভবশক্তি"],context:"m = 5 kg, h = 20 m, g = 10 m/s²",q:"৫ kg ভরের বস্তু ২০ m উচ্চতায় তোলা হলো। বিভবশক্তি কত? (g = 10 m/s²)",opts:["1000 J","250 J","100 J","2000 J"],ans:0,explanation:"PE = mgh = 5×10×20 = 1000 J"},
  {id:39,subjectId:2,levelId:1,tags:["কাজ-শক্তি","ক্ষমতা"],context:"W = 90000 J, t = 5 min = 300 s",q:"একটি মোটর ৫ min-এ ৯০,০০০ J কাজ করে। ক্ষমতা কত?",opts:["300 W","18000 W","450 W","600 W"],ans:0,explanation:"P = W/t = 90000/300 = 300 W"},
  {id:40,subjectId:2,levelId:1,tags:["কাজ-শক্তি","মুক্তপতন","শক্তি সংরক্ষণ"],context:"h = 40 m, g = 10 m/s², u = 0",q:"একটি বস্তু ৪০ m উচ্চতা থেকে পড়ে মাটিতে আঘাত করে। বেগ কত? (g = 10 m/s²)",opts:["20√2 m/s","20 m/s","40 m/s","10√8 m/s"],ans:0,explanation:"v = √(2gh) = √(2×10×40) = √800 = 20√2 m/s"},
  {id:41,subjectId:2,levelId:1,tags:["কাজ-শক্তি","পাম্প","ক্ষমতা"],context:"m = 600 kg, h = 10 m, t = 60 s, g = 10 m/s²",q:"একটি পাম্প ১ min-এ ৬০০ kg পানি ১০ m উপরে তোলে। পাম্পের ক্ষমতা কত?",opts:["1000 W","600 W","100 W","6000 W"],ans:0,explanation:"P = mgh/t = 600×10×10/60 = 1000 W"},
  {id:42,subjectId:2,levelId:1,tags:["কাজ-শক্তি","শক্তি সংরক্ষণ"],context:"m=4 kg, h=5 m, g=10 m/s²",q:"একটি বস্তুর ভর ৪ kg এবং এটি ৫ m উচ্চতা থেকে পড়ছে। মাটিতে পৌঁছানোর আগ মুহূর্তে গতিশক্তি কত? (g=10)",opts:["200 J","100 J","400 J","50 J"],ans:0,explanation:"KE = mgh = 4×10×5 = 200 J (শক্তি সংরক্ষণ সূত্র)"},
  {id:43,subjectId:2,levelId:1,tags:["কাজ-শক্তি","স্প্রিং"],context:"x=0.2 m, PE=4J",q:"একটি স্প্রিং ০.২ m চাপলে স্থিতিশক্তি ৪ J হয়। স্প্রিং ধ্রুবক k কত?",opts:["200 N/m","20 N/m","40 N/m","100 N/m"],ans:0,explanation:"PE = ½kx² → 4 = ½×k×0.04 → k = 200 N/m"},
  {id:44,subjectId:2,levelId:1,tags:["কাজ-শক্তি","kWh"],context:"P=100 W=0.1 kW, t=5h",q:"একটি ১০০ W বাল্ব ৫ ঘণ্টা জ্বললে কত kWh বিদ্যুৎ খরচ হবে?",opts:["0.5 kWh","500 kWh","5 kWh","50 kWh"],ans:0,explanation:"E = P×t = 0.1 kW × 5 h = 0.5 kWh"},

  // পদার্থ SSC — তরঙ্গ-শব্দ
  {id:45,subjectId:2,levelId:1,tags:["তরঙ্গ-শব্দ","তরঙ্গদৈর্ঘ্য"],context:"f = 400 Hz, v = 320 m/s",q:"একটি তরঙ্গের কম্পাঙ্ক ৪০০ Hz এবং বেগ ৩২০ m/s। তরঙ্গদৈর্ঘ্য কত?",opts:["0.8 m","1.25 m","128000 m","0.5 m"],ans:0,explanation:"λ = v/f = 320/400 = 0.8 m"},
  {id:46,subjectId:2,levelId:1,tags:["তরঙ্গ-শব্দ","শব্দ"],context:"v = 340 m/s, f = 850 Hz",q:"শব্দের বেগ ৩৪০ m/s। ৮৫০ Hz কম্পাঙ্কের শব্দের তরঙ্গদৈর্ঘ্য কত?",opts:["0.4 m","2.5 m","0.25 m","4 m"],ans:0,explanation:"λ = v/f = 340/850 = 0.4 m"},
  {id:47,subjectId:2,levelId:1,tags:["তরঙ্গ-শব্দ","প্রতিধ্বনি"],context:"t = 2 s, v = 340 m/s",q:"একটি শব্দ উৎস থেকে প্রতিধ্বনি ২ s পর শোনা গেল। উৎস থেকে প্রাচীরের দূরত্ব কত? (শব্দের বেগ = ৩৪০ m/s)",opts:["340 m","680 m","170 m","700 m"],ans:0,explanation:"শব্দ যায় ও ফেরে → d = vt/2 = 340×2/2 = 340 m"},
  {id:48,subjectId:2,levelId:1,tags:["তরঙ্গ-শব্দ","কম্পাঙ্ক","পর্যায়কাল"],context:"T = 0.005 s",q:"একটি তরঙ্গের পর্যায়কাল ০.০০৫ s। কম্পাঙ্ক কত?",opts:["200 Hz","500 Hz","0.005 Hz","2000 Hz"],ans:0,explanation:"f = 1/T = 1/0.005 = 200 Hz"},
  {id:49,subjectId:2,levelId:1,tags:["তরঙ্গ-শব্দ","কম্পন"],context:"T=0.004 s, t=60 s",q:"একটি সুর শলাকার পর্যায়কাল 0.004 s। এক মিনিটে কতটি কম্পন সম্পন্ন হবে?",opts:["15000","250","1500","60"],ans:0,explanation:"f = 1/T = 250 Hz → কম্পন = 250×60 = 15000"},
  {id:50,subjectId:2,levelId:1,tags:["তরঙ্গ-শব্দ","বজ্রপাত"],context:"t=4s, v=340 m/s",q:"বজ্রপাতের আওয়াজ ৪ s পর শোনা গেল। বজ্রপাত কত দূরে হয়েছে? (শব্দের বেগ=340 m/s)",opts:["1360 m","680 m","340 m","1700 m"],ans:0,explanation:"d = v×t = 340×4 = 1360 m"},
  {id:51,subjectId:2,levelId:1,tags:["তরঙ্গ-শব্দ","বিট"],context:"f₁=256 Hz, f₂=260 Hz",q:"দুটি শব্দের কম্পাঙ্ক ২৫৬ Hz ও ২৬০ Hz। প্রতি সেকেন্ডে বিট সংখ্যা কত?",opts:["4","516","2","8"],ans:0,explanation:"বিট = |f₁−f₂| = |256−260| = 4"},

  // পদার্থ SSC — আলো
  {id:52,subjectId:2,levelId:1,tags:["আলো","অবতল দর্পণ","দর্পণ সূত্র"],context:"f = −15 cm, u = −45 cm",q:"একটি অবতল দর্পণের ফোকাস দূরত্ব ১৫ cm। বস্তু ৪৫ cm সামনে থাকলে প্রতিবিম্বের দূরত্ব কত?",opts:["−22.5 cm","−30 cm","−45 cm","−60 cm"],ans:0,explanation:"1/v = 1/f − 1/u = 1/(−15) − 1/(−45) = −3/45+1/45 = −2/45 → v = −22.5 cm"},
  {id:53,subjectId:2,levelId:1,tags:["আলো","দর্পণ","ফোকাস"],context:"u = −20 cm, v = +60 cm",q:"একটি দর্পণে বস্তু ২০ cm সামনে এবং প্রতিবিম্ব ৬০ cm পেছনে (অসদ)। ফোকাস দূরত্ব কত?",opts:["30 cm","−30 cm","15 cm","60 cm"],ans:0,explanation:"1/f = 1/v+1/u = 1/60+1/(−20) = 1/60−3/60 = −2/60 → f = 30 cm (উত্তল)"},
  {id:54,subjectId:2,levelId:1,tags:["আলো","বক্রতার ব্যাসার্ধ"],context:"R = 40 cm",q:"অবতল দর্পণে বক্রতার ব্যাসার্ধ ৪০ cm। ফোকাস দূরত্ব কত?",opts:["20 cm","80 cm","10 cm","40 cm"],ans:0,explanation:"f = R/2 = 40/2 = 20 cm"},
  {id:55,subjectId:2,levelId:1,tags:["আলো","উত্তল দর্পণ"],context:"f = +25 cm, u = −50 cm",q:"একটি উত্তল দর্পণে ফোকাস দূরত্ব ২৫ cm। বস্তু ৫০ cm সামনে থাকলে প্রতিবিম্ব কোথায়?",opts:["+50/3 cm","−50/3 cm","−25 cm","+25 cm"],ans:0,explanation:"1/v = 1/f−1/u = 1/25−1/(−50) = 2/50+1/50 = 3/50 → v = 50/3 cm"},
  {id:56,subjectId:2,levelId:1,tags:["আলো","সমতল দর্পণ"],context:"u = 30 cm",q:"সমতল দর্পণে একটি বস্তু ৩০ cm সামনে। প্রতিবিম্বের অবস্থান কোথায়?",opts:["দর্পণের ৩০ cm পেছনে","দর্পণের ৩০ cm সামনে","১৫ cm পেছনে","৬০ cm পেছনে"],ans:0,explanation:"সমতল দর্পণে প্রতিবিম্ব দর্পণের পেছনে একই দূরত্বে হয়"},
  {id:57,subjectId:2,levelId:1,tags:["আলো","অবতল দর্পণ"],context:"u=−20 cm, f=−10 cm",q:"একটি অবতল দর্পণে বস্তু ফোকাস দূরত্বের দ্বিগুণ দূরে রাখা হলো (f=10 cm)। প্রতিবিম্ব কোথায় হবে?",opts:["−20 cm","−10 cm","−40 cm","অসীমে"],ans:0,explanation:"1/v = 1/f−1/u = 1/(−10)−1/(−20) = −2/20+1/20 = −1/20 → v = −20 cm"},
  {id:58,subjectId:2,levelId:1,tags:["আলো","বিবর্ধন"],context:"m=−2, u=−15 cm",q:"একটি দর্পণে বিবর্ধন m = −2। বস্তু দর্পণ থেকে ১৫ cm দূরে। প্রতিবিম্ব কোথায়?",opts:["−30 cm","30 cm","−7.5 cm","60 cm"],ans:0,explanation:"m = −v/u → −2 = −v/(−15) → v = −30 cm"},
  {id:59,subjectId:2,levelId:1,tags:["আলো","প্রতিসরণ","প্রতিসরণাঙ্ক"],context:"c=3×10⁸ m/s, v=2×10⁸ m/s",q:"আলোর বেগ ৩×10⁸ m/s। একটি মাধ্যমে বেগ ২×10⁸ m/s হলে প্রতিসরণাঙ্ক কত?",opts:["1.5","0.67","1","2"],ans:0,explanation:"n = c/v = 3×10⁸ / 2×10⁸ = 1.5"},

  // পদার্থ HSC — বিদ্যুৎ
  {id:60,subjectId:2,levelId:2,tags:["বিদ্যুৎ","ওহমের সূত্র","ক্ষমতা"],context:"V = 24 V, R = 8 Ω",q:"V = 24 V, R = 8 Ω হলে তড়িৎপ্রবাহ এবং ক্ষমতা কত?",opts:["I=3A, P=72W","I=2A, P=48W","I=4A, P=96W","I=3A, P=24W"],ans:0,explanation:"I = V/R = 24/8 = 3A → P = VI = 24×3 = 72W"},
  {id:61,subjectId:2,levelId:2,tags:["বিদ্যুৎ","সিরিজ সার্কিট"],context:"R₁=3Ω, R₂=6Ω, R₃=9Ω, V=18V",q:"৩ Ω, ৬ Ω, ৯ Ω তিনটি রেজিস্টর সিরিজে যুক্ত। ১৮ V ব্যাটারি লাগালে তড়িৎপ্রবাহ কত?",opts:["1 A","2 A","3 A","0.5 A"],ans:0,explanation:"R_total = 3+6+9 = 18Ω → I = V/R = 18/18 = 1A"},
  {id:62,subjectId:2,levelId:2,tags:["বিদ্যুৎ","প্যারালাল সার্কিট"],context:"R₁=6Ω, R₂=12Ω, V=12V",q:"৬ Ω ও ১২ Ω সমান্তরালে সংযুক্ত। ১২ V ব্যাটারি লাগালে মোট প্রবাহ কত?",opts:["3 A","1 A","2 A","6 A"],ans:0,explanation:"1/R = 1/6+1/12 = 3/12 → R=4Ω → I=12/4=3A"},
  {id:63,subjectId:2,levelId:2,tags:["বিদ্যুৎ","শক্তি","হিটার"],context:"V=220V, I=5A, t=3600s",q:"একটি হিটার ২২০ V সরবরাহে ৫ A তড়িৎ নেয়। ১ ঘণ্টায় কত এনার্জি খরচ হয়?",opts:["3960000 J","1100 J","1100 W","396 J"],ans:0,explanation:"E = VIt = 220×5×3600 = 3,960,000 J"},
  {id:64,subjectId:2,levelId:2,tags:["বিদ্যুৎ","রেজিস্ট্যান্স","বাল্ব"],context:"P = 60 W, V = 220 V",q:"একটি বাল্ব ৬০ W, ২২০ V। রেজিস্ট্যান্স কত?",opts:["≈ 807 Ω","60 Ω","220 Ω","13200 Ω"],ans:0,explanation:"R = V²/P = 220²/60 = 48400/60 ≈ 807 Ω"},
  {id:65,subjectId:2,levelId:2,tags:["বিদ্যুৎ","জুলের সূত্র","তাপ"],context:"I=2A, R=5Ω, t=30s",q:"I = 2 A, R = 5 Ω হলে ৩০ s-এ কত তাপ উৎপন্ন হবে?",opts:["600 J","300 J","150 J","1200 J"],ans:0,explanation:"H = I²Rt = 4×5×30 = 600 J"},
  {id:66,subjectId:2,levelId:2,tags:["বিদ্যুৎ","ভোল্টেজ ড্রপ"],context:"R=4Ω, I=3A",q:"৪ Ω রেজিস্টরে ৩ A তড়িৎ প্রবাহিত হলে ভোল্টেজ ড্রপ কত?",opts:["12 V","1.33 V","7 V","43 V"],ans:0,explanation:"V = IR = 3×4 = 12 V"},
  {id:67,subjectId:2,levelId:2,tags:["বিদ্যুৎ","তুল্য রোধ","সমান্তরাল"],context:"R₁=R₂=10Ω",q:"দুটি ১০ Ω রেজিস্টর সমান্তরালে। তুল্য রোধ কত?",opts:["5 Ω","20 Ω","10 Ω","1 Ω"],ans:0,explanation:"1/R = 1/10+1/10 = 2/10 → R = 5 Ω"},
  {id:68,subjectId:2,levelId:2,tags:["বিদ্যুৎ","অভ্যন্তরীণ রোধ","টার্মিনাল ভোল্টেজ"],context:"E=6V, r=2Ω, R=4Ω",q:"একটি বর্তনীতে ৬ V ব্যাটারি ও ২ Ω অভ্যন্তরীণ রোধ এবং ৪ Ω বাহ্যিক রোধ। প্রবাহ ও টার্মিনাল ভোল্টেজ কত?",opts:["I=1A, V=4V","I=2A, V=2V","I=3A, V=0V","I=1.5A, V=3V"],ans:0,explanation:"I = E/(R+r) = 6/(4+2) = 1A → V = IR = 1×4 = 4V"},
,
  {id:200,subjectId:2,levelId:3,q:"একটি স্প্রিং ০.২ m চাপলে স্থিতিশক্তি ৪ J হয়। স্প্রিং ধ্রুবক k কত?",context:"x=0.2 m, PE=4J",opts:["200 N/m","20 N/m","40 N/m","100 N/m"],ans:0,explanation:"PE = ½kx² → 4 = ½×k×0.04 → k = 8/0.04 = 200 N/m"},
  {id:201,subjectId:2,levelId:3,q:"পৃথিবীর পূর্ণ শক্তির কত অংশ শোষিত হয়?",opts:["ক) ⅓","খ) ½","গ) ¼","ঘ) ⅔"],ans:2,explanation:"পৃথিবী একটি গোলক — সূর্যের সমান্তরাল আলোর কার্যকর ক্ষেত্রফল = πr², মোট পৃষ্ঠতল = 4πr²। তাই শোষিত শক্তি = মোটের ¼।"},
  {id:202,subjectId:2,levelId:3,q:"v = 320 m/s এবং λ = 8 m হলে কম্পাঙ্ক f কত?",opts:["25 Hz","40 Hz","80 Hz","328 Hz"],ans:1,explanation:"f = v/λ = 320/8 = 40 Hz। সম্পর্ক: v = fλ → f = v/λ।"},
  {id:203,subjectId:2,levelId:3,q:"দুটো আধানের মধ্যে দূরত্ব দ্বিগুণ করলে তাদের মধ্যে তড়িৎ বল কতটুকু হবে?",opts:["দ্বিগুণ হবে","অর্ধেক হবে","এক-চতুর্থাংশ হবে","অপরিবর্তিত থাকবে"],ans:2,explanation:"F ∝ 1/r²। r দ্বিগুণ হলে r² চারগুণ → বল হয় 1/4 ভাগ। এটাই কুলম্বের সূত্রের বিপরীত বর্গ সম্পর্ক।"},
  {id:204,subjectId:2,levelId:3,q:"v-t গ্রাফে t=0 তে v=10 m/s, t=10s তে v=80 m/s। ত্বরণ কত?",context:"v-t গ্রাফে একটি সরলরেখা দেখা যাচ্ছে।",opts:["5 m/s²","7 m/s²","8 m/s²","10 m/s²"],ans:1,explanation:"a = Δv/Δt = (80−10)/10 = 70/10 = 7 m/s²। v-t গ্রাফের ঢাল = ত্বরণ।"},
  {id:205,subjectId:2,levelId:3,q:"কোন নিউক্লিয়ার বল খুব দুর্বল হয় — কোন দূরত্বে?",opts:["10⁻⁹ m","10⁻¹⁵ m","10⁻¹⁸ m","10⁻²¹ m"],ans:3,explanation:"দূরত্ব যত বেশি → nuclear force তত দুর্বল। 10⁻²¹ m দূরত্বে নিউক্লিয়ার বল অত্যন্ত দুর্বল হয়।"},
  {id:206,subjectId:2,levelId:3,q:"আলোর প্রতিফলনের ক্ষেত্রে — i. আপতন কোণ ii. প্রতিফলন কোণ iii. 30° কোণ — কোনটি সঠিক?",opts:["i ও ii","i ও iii","ii ও iii","i, ii ও iii"],ans:0,explanation:"Law of reflection: angle of incidence = angle of reflection — তাই i ও ii সঠিক।"},
  {id:207,subjectId:2,levelId:3,q:"f=15 cm অবতল দর্পণে বস্তু u=−10 cm রাখলে (F-এর ভেতরে) প্রতিবিম্ব কেমন হবে?",opts:["বাস্তব ও উল্টো","অবাস্তব ও সোজা","অসীমে","বাস্তব ও সোজা"],ans:1,explanation:"1/v = 1/f − 1/u = 1/(−15) − 1/(−10) = −1/15 + 1/10 = 1/30 → v = +30 cm। ধনাত্মক v → দর্পণের পেছনে → অবাস্তব, সোজা ও বড়।"},
  {id:208,subjectId:2,levelId:3,q:"একটি গাড়ির u=10 m/s এবং a=3 m/s²। 5 সেকেন্ড পরে বেগ কত?",opts:["15 m/s","20 m/s","25 m/s","30 m/s"],ans:2,explanation:"v = u + at = 10 + 3×5 = 10 + 15 = 25 m/s। গতির প্রথম সমীকরণ।"},
  {id:209,subjectId:2,levelId:3,q:"তাড়িক শক্তির মাত্রা কোনটি?",opts:["[MLT⁻¹]","[MLT⁻²]","[ML²T⁻¹]","[ML²T⁻²]"],ans:3,explanation:"শক্তি = বল × দূরত্ব। বলের মাত্রা [MLT⁻²] × দূরত্ব [L] = [ML²T⁻²]। সব ধরনের শক্তির মাত্রা একই।"},
  {id:210,subjectId:2,levelId:3,q:"তরঙ্গচিত্রে 0 থেকে 4m পর্যন্ত একটি পূর্ণ তরঙ্গ — তরঙ্গদৈর্ঘ্য (λ) কত?",opts:["2m","4m","8m","12m"],ans:1,explanation:"λ = একটি পূর্ণ চক্রের দৈর্ঘ্য। গ্রাফে 0 থেকে 4m পর্যন্ত একটি পূর্ণ তরঙ্গ → λ = 4m।"},
  {id:211,subjectId:2,levelId:3,q:"v-t গ্রাফে রেখা ওপর থেকে নিচে যাচ্ছে। u=40 m/s, 8s পর v=0। মন্দন কত?",opts:["8 m/s²","5 m/s²","4 m/s²","10 m/s²"],ans:1,explanation:"a = (v−u)/t = (0−40)/8 = −5 m/s²। ঋণাত্মক চিহ্ন মানে মন্দন। মন্দনের মান = 5 m/s²।"},
  {id:212,subjectId:2,levelId:3,q:"s-t গ্রাফে বাঁকা (curved) রেখা কী নির্দেশ করে?",opts:["সুষম বেগ","বিরামহীন গতি","অসুষম গতি","শূন্য বেগ"],ans:2,explanation:"s-t গ্রাফে সরলরেখা = সুষম বেগ। বাঁকা রেখা মানে ঢাল বদলাচ্ছে → বেগ বদলাচ্ছে → অসুষম গতি।"},
  {id:213,subjectId:2,levelId:3,q:"গ্রাফে তরঙ্গের বিস্তার (amplitude) — মোট উচ্চতা 12cm হলে বিস্তার কত?",opts:["12cm","6cm","3cm","9cm"],ans:1,explanation:"বিস্তার = সাম্যাবস্থান থেকে সর্বোচ্চ সরণ = 6 cm। মোট উচ্চতা 12 cm হলেও বিস্তার অর্ধেক = 6 cm।"},
  {id:214,subjectId:2,levelId:3,q:"তরঙ্গদৈর্ঘ্য λ=2m এবং কম্পাঙ্ক f=50 Hz হলে তরঙ্গবেগ কত?",opts:["25 m/s","52 m/s","100 m/s","200 m/s"],ans:2,explanation:"v = fλ = 50 × 2 = 100 m/s। তরঙ্গবেগ = কম্পাঙ্ক × তরঙ্গদৈর্ঘ্য।"},
  {id:215,subjectId:2,levelId:3,q:"v-t গ্রাফে v=20 m/s সমান (constant)। 6 সেকেন্ডে মোট সরণ কত?",opts:["20 m","60 m","120 m","240 m"],ans:2,explanation:"সরণ = v × t = 20 × 6 = 120 m। v-t গ্রাফের নিচের ক্ষেত্রফল = সরণ।"},
  {id:216,subjectId:2,levelId:3,q:"পরিমাপের বৈজ্ঞানিক পদ্ধতির প্রবর্তক কে?",opts:["নিউটন","কেপলার","গ্যালিলিও","আইনস্টাইন"],ans:2,explanation:"Galileo Galilei আধুনিক বৈজ্ঞানিক পদ্ধতির জনক।"},
  {id:217,subjectId:2,levelId:3,q:"f=15 cm অবতল দর্পণে u=−20 cm রাখলে (ফোকাস দূরত্বের দ্বিগুণ) প্রতিবিম্ব কোথায়?",context:"u=−20 cm, f=−10 cm",opts:["−20 cm","−10 cm","−40 cm","অসীমে"],ans:0,explanation:"1/v = 1/f − 1/u = 1/(−10) − 1/(−20) = −1/10 + 1/20 = −1/20 → v = −20 cm।"},
  {id:218,subjectId:2,levelId:3,q:"গ্রাফ থেকে f = 2.5 Hz। পর্যায়কাল T কত?",opts:["2.5s","0.4s","0.25s","5s"],ans:1,explanation:"T = 1/f = 1/2.5 = 0.4 s। পর্যায়কাল ও কম্পাঙ্ক পরস্পরের বিপরীত।"},
  {id:219,subjectId:2,levelId:3,q:"একটি বল 40 kg সিঁড়ি বেয়ে 20 ধাপ উঠল, প্রতি ধাপে উচ্চতা 15 cm। কাজ কত?",opts:["128 J","83.626 J","1176 J","1254.4 J"],ans:3,explanation:"মোট উচ্চতা = 20 × 0.15 = 3 m। কাজ = mgh = 40 × 9.8 × 3 = 1176 J → নিকটতম বিকল্প 1254.4 J।"},
  {id:220,subjectId:2,levelId:3,q:"k = 500 N/m স্প্রিং 0.3 m চাপলে প্রত্যানয়ন বল কত হবে?",opts:["50 N","100 N","150 N","200 N"],ans:2,explanation:"F = kx = 500 × 0.3 = 150 N। হুকের সূত্র: বল = স্প্রিং ধ্রুবক × সংকোচন।"},
  {id:221,subjectId:2,levelId:3,q:"স্প্রিং A (k=100 N/m) ও B (k=200 N/m) — দুটোকেই 0.1 m চাপলে কোনটার সঞ্চিত শক্তি বেশি?",opts:["দুটো সমান","B-এর বেশি","A-এর বেশি","বলা যাবে না"],ans:1,explanation:"PE = ½kx²। A: ½×100×0.01 = 0.5 J। B: ½×200×0.01 = 1 J। k বেশি হলে PE বেশি — তাই B > A।"},
  {id:222,subjectId:2,levelId:3,q:"আলোর বেগ ৩×10⁸ m/s। একটি মাধ্যমে বেগ ২×10⁸ m/s হলে প্রতিসরণাঙ্ক কত?",opts:["1.5","0.67","1","2"],ans:0,explanation:"n = c/v = 3×10⁸ / 2×10⁸ = 1.5। প্রতিসরণাঙ্ক সবসময় ≥ 1।"},
  {id:223,subjectId:2,levelId:3,q:"তড়িৎ বলরেখা সম্পর্কে কোন বক্তব্যটি সঠিক?",opts:["ঋণাত্মক আধান থেকে বের হয়","ধনাত্মক আধান থেকে বের হয়","দুটি বলরেখা পরস্পর ছেদ করতে পারে","বলরেখা বৃত্তাকার পথে চলে"],ans:1,explanation:"বলরেখা ধনাত্মক (+) আধান থেকে বের হয়, ঋণাত্মক (−) আধানে প্রবেশ করে। দুটি বলরেখা কখনো পরস্পর ছেদ করে না।"},
  {id:224,subjectId:2,levelId:3,q:"চিত্রানুযায়ী A বস্তুর সাপেক্ষে B বস্তুর তড়িৎ তীব্রতা কত? (F = 3.6×10¹¹ N, q = 1C)",opts:["1.8 × 10¹⁰ NC⁻¹","4.5 × 10¹¹ NC⁻¹","9.0 × 10¹⁰ NC⁻¹","1.8 × 10⁹ NC⁻¹"],ans:0,explanation:"E = F/q = 3.6×10¹¹ / 20 = 1.8×10¹⁰ NC⁻¹। তড়িৎ তীব্রতা = বল / আধান।"},
  {id:225,subjectId:2,levelId:3,q:"120 MeV = কত Joule?",opts:["1.92×10⁻¹¹ J","1.92×10⁻¹³ J","1.92×10⁻¹² J","1.92×10⁻¹⁰ J"],ans:0,explanation:"1 eV = 1.6×10⁻¹⁹ J → 1 MeV = 1.6×10⁻¹³ J → 120 MeV = 120 × 1.6×10⁻¹³ = 1.92×10⁻¹¹ J।"},
  {id:226,subjectId:2,levelId:3,q:"একটি পরিবাহীকে আহিত করলে আধান কোথায় জমা হয়?",opts:["সমগ্র আয়তনে সমানভাবে","শুধু বাইরের পৃষ্ঠে","শুধু কেন্দ্রে","ভেতরে ও বাইরে সমানভাবে"],ans:1,explanation:"পরিবাহীর মুক্ত ইলেকট্রনগুলো পরস্পরকে বিকর্ষণ করে বাইরের পৃষ্ঠে জমা হয়। ভেতরে তড়িৎক্ষেত্র = শূন্য।"},
  {id:227,subjectId:2,levelId:3,q:"OR রশ্মির প্রতিফলন — দর্পণ 45° কোণে হেলানো। প্রতিফলন কোণ কত?",opts:["35°","45°","55°","65°"],ans:1,explanation:"দর্পণ 45° কোণে হেলানো হলে OR রশ্মির প্রতিফলন কোণ = 45°।"},
  {id:228,subjectId:2,levelId:3,q:"চিত্রানুযায়ী A ও B বস্তু পরিবাহী তার দ্বারা যুক্ত করলে — A=50C, B=0C — ইলেকট্রন কোন দিকে যাবে?",opts:["i ও ii","শুধু ii","iii — B থেকে A দিকে","i, ii ও iii"],ans:2,explanation:"A তে ধনাত্মক চার্জ বেশি (ইলেকট্রন কম), তাই ইলেকট্রন B থেকে A এর দিকে প্রবাহিত হবে।"},
  {id:229,subjectId:2,levelId:3,q:"বস্তুর স্থানান্তরের সাথে অবস্থানের পরিবর্তন — পথ M, ত্বরণ V, চূড়ান্ত বেগ VC হলে সমীকরণ কোনটি?",opts:["L = M + V + VC","L = M + V – VC","L = M – V + VC","L = M – V – VC"],ans:2,explanation:"Displacement এর ধারণাগত রূপ: L = M – V + VC।"}
];


// ═══════════════ STATE ═══════════════
let subjects    = JSON.parse(localStorage.getItem('mq_subjects')    ||'null')||DEF_SUBJECTS.map(s=>({...s}));
let levels      = JSON.parse(localStorage.getItem('mq_levels')      ||'null')||DEF_LEVELS.map(l=>({...l}));
let questions   = JSON.parse(localStorage.getItem('mq_questions')   ||'null')||DEF_QUESTIONS.map(q=>({...q}));
let participants= JSON.parse(localStorage.getItem('mq_participants')||'[]');

// ── Version-based merge: ensure new default questions always exist ──
(function mergeDefaultQuestions(){
  const DATA_VERSION = 3; // bump this when new default questions are added
  const savedVer = parseInt(localStorage.getItem('mq_data_ver')||'0');
  if(savedVer < DATA_VERSION){
    // Ensure all DEF_SUBJECTS exist
    DEF_SUBJECTS.forEach(ds=>{if(!subjects.find(s=>s.id===ds.id))subjects.push({...ds});});
    // Ensure all DEF_LEVELS exist
    DEF_LEVELS.forEach(dl=>{if(!levels.find(l=>l.id===dl.id))levels.push({...dl});});
    // Ensure all DEF_QUESTIONS exist (add missing ones by id)
    const existingIds = new Set(questions.map(q=>q.id));
    DEF_QUESTIONS.forEach(dq=>{if(!existingIds.has(dq.id))questions.push({...dq});});
    localStorage.setItem('mq_subjects',JSON.stringify(subjects));
    localStorage.setItem('mq_levels',JSON.stringify(levels));
    localStorage.setItem('mq_questions',JSON.stringify(questions));
    localStorage.setItem('mq_data_ver',String(DATA_VERSION));
  }
})();

let quizOptions = JSON.parse(localStorage.getItem('mq_quiz_options')||'null') || {shuffle:false, showExplanation:true, randomQ:true};

let selSubjectId= null, selLevelId= null;
let currentPlayer='', currentSchool='', quizQuestions=[], currentQ=0, score=0;
let answered=false, timerInterval=null, globalTimeLeft=TOTAL_SECONDS;
let editingQId=null, editingSubjId=null, editingLvlId=null;
let selEmoji='🧮';
let currentTags=[];
let currentWordLinks=[];
let importData=null;

const sv=(k,v)=>localStorage.setItem(k,JSON.stringify(v));
const nid=arr=>arr.length?Math.max(...arr.map(x=>x.id))+1:1;
const esc=t=>String(t).replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;');


// ═══════════════ NAV ═══════════════

function goTo(id){
  document.querySelectorAll('.screen').forEach(s=>s.classList.remove('active'));
  document.getElementById(id).classList.add('active');
}


// ═══════════════ SUBJECT SELECT ═══════════════

function renderSubjectGrid(){
  const g=document.getElementById('subject-grid');
  if(!subjects.length){g.innerHTML='<div style="grid-column:1/-1;color:var(--muted);padding:20px;text-align:center;">কোনো বিষয় নেই। Admin থেকে যোগ করুন।</div>';return;}
  g.innerHTML=subjects.map(s=>{
    const cnt=questions.filter(q=>q.subjectId===s.id).length;
    const sel=selSubjectId===s.id;
    return `<div class="sel-card ${sel?'selected':''}" onclick="pickSubject(${s.id})"
      style="border-color:${sel?s.color:'var(--border)'};${sel?'box-shadow:0 0 0 2px '+s.color+'40':''}">
      <div class="sel-check" style="color:${s.color}">✅</div>
      <div class="sel-icon">${s.emoji}</div>
      <div class="sel-name" style="color:${sel?s.color:'var(--text)'}">${esc(s.name)}</div>
      <div class="sel-sub">${cnt} টি প্রশ্ন</div>
    </div>`;
  }).join('');
}

function pickSubject(id){selSubjectId=id;document.getElementById('subject-error').textContent='';renderSubjectGrid();}


function goToSelectLevel(){
  if(!selSubjectId){document.getElementById('subject-error').textContent='⚠️ একটি বিষয় বেছে নাও!';return;}
  const s=subjects.find(x=>x.id===selSubjectId);
  document.getElementById('level-screen-sub').textContent=`${s.emoji} ${s.name} — তোমার শ্রেণি বেছে নাও`;
  renderLevelGrid(); goTo('screen-select-level');
}


// ═══════════════ LEVEL SELECT ═══════════════

function renderLevelGrid(){
  const g=document.getElementById('level-grid');
  if(!levels.length){g.innerHTML='<div style="grid-column:1/-1;color:var(--muted);padding:20px;text-align:center;">কোনো Level নেই। Admin থেকে যোগ করুন।</div>';return;}
  g.innerHTML=levels.map(l=>{
    const cnt=questions.filter(q=>q.subjectId===selSubjectId&&q.levelId===l.id).length;
    const sel=selLevelId===l.id;
    return `<div class="sel-card ${sel?'selected':''}" onclick="pickLevel(${l.id})"
      style="border-color:${sel?'var(--purple)':'var(--border)'};${sel?'box-shadow:0 0 0 2px rgba(167,139,250,.35)':''}">
      <div class="sel-check" style="color:var(--purple)">✅</div>
      <div class="sel-icon">🏫</div>
      <div class="sel-name" style="color:${sel?'var(--purple)':'var(--text)'}">${esc(l.name)}</div>
      <div class="sel-sub">${cnt} টি প্রশ্ন</div>
    </div>`;
  }).join('');
}

function pickLevel(id){selLevelId=id;document.getElementById('level-error').textContent='';renderLevelGrid();}


function goToJoin(){
  if(!selLevelId){document.getElementById('level-error').textContent='⚠️ একটি Level বেছে নাও!';return;}
  const qCount=questions.filter(q=>q.subjectId===selSubjectId&&q.levelId===selLevelId).length;
  if(!qCount){document.getElementById('level-error').textContent='⚠️ এই Level-এ কোনো প্রশ্ন নেই!';return;}
  const s=subjects.find(x=>x.id===selSubjectId), l=levels.find(x=>x.id===selLevelId);
  document.getElementById('join-info-label').textContent=`${s.emoji} ${s.name} · ${l.name} · ${qCount} প্রশ্ন · ${qCount} নম্বর`;
  // Update countdown ring with current timer setting
  const mins=(parseInt(localStorage.getItem('mq_timer_min'))||30);
  const jcwTime=document.querySelector('.jcw-time');
  if(jcwTime)jcwTime.textContent=`${String(mins).padStart(2,'0')}:০০`;
  goTo('screen-join');
}


// ═══════════════ START QUIZ ═══════════════

function startQuiz(){
  const name=document.getElementById('input-name').value.trim();
  const school=document.getElementById('input-school').value.trim();
  if(!name){document.getElementById('join-error').textContent='⚠️ নাম লিখতে ভুলে গেছো!';return;}
  if(!school){document.getElementById('join-error').textContent='⚠️ স্কুল/কলেজের নাম লিখো!';return;}
  document.getElementById('join-error').textContent='';
  currentPlayer=name;
  currentSchool=school;
  TOTAL_SECONDS = (parseInt(localStorage.getItem('mq_timer_min'))||30) * 60;
  let qs = questions.filter(q=>q.subjectId===selSubjectId&&q.levelId===selLevelId);
  if(quizOptions.randomQ) qs = qs.sort(()=>Math.random()-.5);
  quizQuestions = qs.map(q=>{
    let opts = [...q.opts];
    let ans = q.ans;
    if(quizOptions.shuffle){
      const indices = [0,1,2,3];
      const shuffled = indices.sort(()=>Math.random()-.5);
      opts = shuffled.map(i=>q.opts[i]);
      ans = shuffled.indexOf(q.ans);
    }
    return {...q, opts, ans, _selected:undefined};
  });
  currentQ=0; score=0; globalTimeLeft=TOTAL_SECONDS;

  const s=subjects.find(x=>x.id===selSubjectId), l=levels.find(x=>x.id===selLevelId);
  const totalMarks = quizQuestions.reduce((acc,q)=>acc+(q.marks||1),0);
  document.getElementById('quiz-player-name').textContent='👤 '+currentPlayer;
  document.getElementById('quiz-info-pills').innerHTML=`
    <span class="info-pill" style="background:${s.color}20;border-color:${s.color}60;color:${s.color}">${s.emoji} ${esc(s.name)}</span>
    <span class="info-pill" style="background:rgba(167,139,250,.12);border-color:rgba(167,139,250,.35);color:var(--purple)">🏫 ${esc(l.short||l.name)}</span>
    <span class="info-pill" style="background:rgba(56,178,245,.1);border-color:rgba(56,178,245,.3);color:var(--blue)">🏛️ ${esc(currentSchool)}</span>
    <span class="info-pill" style="background:rgba(67,233,123,.1);border-color:rgba(67,233,123,.3);color:var(--green)">📝 ${quizQuestions.length} প্রশ্ন · ${totalMarks} নম্বর</span>`;

  goTo('screen-quiz'); startGlobalTimer(); renderQuestion();
}


// ═══════════════ TIMER ═══════════════

function startGlobalTimer(){
  clearInterval(timerInterval); updateTimerUI();
  timerInterval=setInterval(()=>{globalTimeLeft--;updateTimerUI();if(globalTimeLeft<=0){clearInterval(timerInterval);onTimeUp();}},1000);
}

function updateTimerUI(){
  const m=Math.floor(globalTimeLeft/60),s=globalTimeLeft%60;
  const txt=`${String(m).padStart(2,'0')}:${String(s).padStart(2,'0')}`;
  const d=document.getElementById('timer-display'),b=document.getElementById('timer-badge');
  if(d)d.textContent=txt; if(b)b.classList.toggle('warn',globalTimeLeft<=300);
}

function onTimeUp(){
  document.querySelectorAll('.option-btn').forEach(b=>b.disabled=true);
  document.getElementById('next-btn').style.display='none';
  const mins=Math.round(TOTAL_SECONDS/60);
  showToast(`⏰ ${mins} মিনিট শেষ! Quiz জমা হচ্ছে…`,'wrong-t');
  setTimeout(showResult,1800);
}


// ═══════════════ RENDER QUESTION ═══════════════

function renderWordLinkedText(text, wordLinks){
  if(!wordLinks||!wordLinks.length) return esc(text);
  // Sort by word length desc to avoid substring issues
  const sorted=[...wordLinks].sort((a,b)=>b.word.length-a.word.length);
  // Build html safely — replace each linked word with a span
  let result = esc(text);
  sorted.forEach(({word,url})=>{
    const escapedWord = esc(word);
    // replace first occurrence only (to avoid double-replacing)
    result = result.replace(escapedWord,
      `<span class="q-linked-word" onclick="openWordLink('${encodeURIComponent(url)}')" title="🔗 ${esc(url)}">${escapedWord}<sup style="font-size:.55em;opacity:.6">🔗</sup></span>`);
  });
  return result;
}

function openWordLink(encodedUrl){
  window.open(decodeURIComponent(encodedUrl),'_blank','noopener');
}


function renderQuestion(){
  const total=quizQuestions.length,q=quizQuestions[currentQ];
  answered=false;
  document.getElementById('q-num').textContent=`প্রশ্ন ${currentQ+1} / ${total}`;
  document.getElementById('progress-bar').style.width=`${((currentQ+1)/total)*100}%`;
  document.getElementById('next-btn').style.display='none';

  // Per-question marks badge
  const markBadge = document.getElementById('q-mark-badge');
  if(markBadge) {
    const m = q.marks||1;
    markBadge.textContent = `✦ ${m} নম্বর`;
    markBadge.className = m>1 ? 'mark-badge-custom' : 'mark-badge';
  }

  const ctx=document.getElementById('context-box');
  if(q.context){ctx.textContent='📌 '+q.context;ctx.style.display='block';}else ctx.style.display='none';

  // Image
  const imgWrap = document.getElementById('q-image-display');
  if(imgWrap){
    if(q.image){imgWrap.innerHTML=`<div class="q-image-wrap"><img src="${esc(q.image)}" alt="প্রশ্নের ছবি" onerror="this.parentElement.style.display='none'"/></div>`;imgWrap.style.display='block';}
    else{imgWrap.style.display='none';imgWrap.innerHTML='';}
  }

  // Question text with word links
  const qtEl=document.getElementById('q-text');
  if(q.wordLinks&&q.wordLinks.length){
    qtEl.innerHTML=renderWordLinkedText(q.q, q.wordLinks);
  } else {
    qtEl.textContent=q.q;
  }

  const letters=['ক','খ','গ','ঘ'],c=document.getElementById('options-container');
  c.innerHTML='';
  q.opts.forEach((opt,i)=>{
    const btn=document.createElement('button');
    btn.className='option-btn';
    btn.innerHTML=`<span class="option-letter">${letters[i]}</span>${esc(opt)}`;
    btn.onclick=()=>selectOption(i,btn); c.appendChild(btn);
  });
}

function selectOption(index,btn){
  if(answered)return; answered=true;
  quizQuestions[currentQ]._selected=index;
  if(index===quizQuestions[currentQ].ans) score+=(quizQuestions[currentQ].marks||1);
  document.querySelectorAll('.option-btn').forEach(b=>b.disabled=true);
  btn.classList.add('selected-opt');
  document.getElementById('next-btn').style.display='block';
}

function nextQuestion(){currentQ++;if(currentQ>=quizQuestions.length)showResult();else renderQuestion();}


// ═══════════════ RESULT ═══════════════

function showResult(){
  clearInterval(timerInterval);
  const total=quizQuestions.length;
  const fullMarks=quizQuestions.reduce((acc,q)=>acc+(q.marks||1),0);
  const pct=fullMarks>0?Math.round((score/fullMarks)*100):0;
  const timeTaken=TOTAL_SECONDS-globalTimeLeft;
  const mm=Math.floor(timeTaken/60),ss=timeTaken%60;

  document.getElementById('result-score').textContent=`${score} / ${fullMarks}`;
  document.getElementById('result-time-taken').textContent=`⏱️ সময়: ${mm} মিনিট ${ss} সেকেন্ড`;

  const correct=quizQuestions.filter(q=>q._selected===q.ans).length;
  const wrong=quizQuestions.filter(q=>q._selected!==undefined&&q._selected!==q.ans).length;
  const skip=quizQuestions.filter(q=>q._selected===undefined).length;
  document.getElementById('result-marks-row').innerHTML=`
    <div class="result-mark-box"><div class="rmb-val" style="color:var(--green)">${correct}</div><div class="rmb-lbl">সঠিক</div></div>
    <div class="result-mark-box"><div class="rmb-val" style="color:var(--accent2)">${wrong}</div><div class="rmb-lbl">ভুল</div></div>
    <div class="result-mark-box"><div class="rmb-val" style="color:var(--muted)">${skip}</div><div class="rmb-lbl">Skip</div></div>
    <div class="result-mark-box"><div class="rmb-val" style="color:var(--accent)">${pct}%</div><div class="rmb-lbl">শতাংশ</div></div>`;

  let icon,msg;
  if(pct>=90){icon='🏆';msg='অসাধারণ! তুমি জিনিয়াস!';}
  else if(pct>=70){icon='🌟';msg='চমৎকার! অনেক ভালো করেছো!';}
  else if(pct>=50){icon='👍';msg='ভালো চেষ্টা! আরো পড়ো।';}
  else{icon='📚';msg='হতাশ হয়ো না, আবার চেষ্টা করো!';}
  document.getElementById('result-icon').textContent=icon;
  document.getElementById('result-msg').textContent=msg;
  document.getElementById('review-summary').textContent=`✅${correct} ❌${wrong} ⬜${skip}`;

  const showExp = quizOptions.showExplanation;
  const letters=['ক','খ','গ','ঘ'];
  document.getElementById('result-review').innerHTML=quizQuestions.map((q,i)=>{
    const sel=q._selected,correctAns=q.ans,isRight=sel===correctAns,unanswered=sel===undefined;
    const cls=unanswered?'ri-skip':isRight?'ri-correct':'ri-wrong';
    const qMarks=q.marks||1;
    const earnedMarks=isRight?qMarks:0;
    const markTxt=isRight?`+${earnedMarks} নম্বর`:unanswered?'০ নম্বর':'০ নম্বর';
    const markColor=isRight?'var(--green)':unanswered?'var(--muted)':'var(--accent2)';
    const tagsHtml=q.tags&&q.tags.length?`<div style="display:flex;gap:4px;flex-wrap:wrap;margin-top:4px;">${q.tags.map(t=>`<span style="background:rgba(167,139,250,.12);border:1px solid rgba(167,139,250,.3);color:var(--purple);border-radius:20px;padding:1px 7px;font-size:.7rem;">#${esc(t)}</span>`).join('')}</div>`:'';
    const imgHtml=q.image?`<div style="margin-bottom:7px;"><img src="${esc(q.image)}" alt="" style="max-height:100px;border-radius:8px;border:1px solid var(--border);" onerror="this.style.display='none'"/></div>`:'';
    const expHtml=(showExp&&q.explanation)?`<div class="explanation-box"><strong>💡 ব্যাখ্যা</strong>${esc(q.explanation)}</div>`:'';
    return `<div class="review-item ${cls}">
      <div class="review-q-num">
        <span>প্রশ্ন ${i+1} · ${unanswered?'⬜ উত্তর দেওয়া হয়নি':isRight?'✅ সঠিক':'❌ ভুল'}</span>
        <span class="review-q-mark" style="color:${markColor}">${markTxt}</span>
      </div>
      ${tagsHtml}
      ${q.context?`<div style="font-size:.75rem;color:var(--blue);margin-bottom:3px;">📌 ${esc(q.context)}</div>`:''}
      ${imgHtml}
      <div class="review-q-text">${q.wordLinks&&q.wordLinks.length ? renderWordLinkedText(q.q,q.wordLinks) : esc(q.q)}</div>
      <div class="review-opts">${q.opts.map((o,oi)=>{
        let cls2='';
        if(oi===correctAns)cls2='r-correct';
        else if(oi===sel&&!isRight)cls2='r-wrong';
        return `<div class="review-opt ${cls2}"><span class="r-letter">${letters[oi]}</span>${esc(o)}${oi===correctAns?' ✅':''}${oi===sel&&!isRight?' ❌':''}</div>`;
      }).join('')}</div>
      ${expHtml}
    </div>`;
  }).join('');

  const s=subjects.find(x=>x.id===selSubjectId), l=levels.find(x=>x.id===selLevelId);
  const entry={name:currentPlayer,school:currentSchool,subject:s?.name||'',subjectEmoji:s?.emoji||'',subjectColor:s?.color||'',level:l?.name||'',levelShort:l?.short||'',score,fullMarks,pct,correct,wrong,skip,timeSec:timeTaken,timeStr:`${mm}মি ${ss}সে`,date:new Date().toLocaleString('bn-BD')};
  participants.push(entry);
  sv('mq_participants',participants);

  // Rank calculation after saving
  const ranked=getRankedList(s?.name||null,l?.name||null);
  const myIdx=ranked.length-1; // last inserted with same score/time
  // find actual position by matching last entry
  let myRank=ranked.findIndex(p=>p===participants[participants.length-1])+1;
  if(myRank<=0) myRank=ranked.findIndex(p=>p.name===currentPlayer&&p.score===score&&p.timeSec===timeTaken)+1||ranked.length;
  const rankEmojis=['🥇','🥈','🥉'];
  const rankDisplay=myRank===1?'🥇':myRank===2?'🥈':myRank===3?'🥉':`#${myRank}`;
  document.getElementById('my-rank-num').textContent=rankDisplay;
  document.getElementById('my-rank-out-of').textContent=`${ranked.length} জনের মধ্যে ${myRank} তম স্থান`;
  document.getElementById('my-rank-label').textContent=`${s?.emoji||''} ${s?.name||''} · ${l?.name||''} · 🏛️ ${currentSchool}`;

  goTo('screen-result');
}

function playAgain(){
  document.getElementById('input-name').value=currentPlayer;
  document.getElementById('input-school').value=currentSchool;
  document.getElementById('join-error').textContent='';
  goTo('screen-join');
}


// ═══════════════ RANK HELPER ═══════════════

function getRankedList(filterSubj=null,filterLvl=null){
  let list=[...participants];
  if(filterSubj) list=list.filter(p=>p.subject===filterSubj);
  if(filterLvl)  list=list.filter(p=>p.level===filterLvl);
  return list.sort((a,b)=>b.score-a.score||a.timeSec-b.timeSec);
}


// ═══════════════ PUBLIC LEADERBOARD ═══════════════
let lbCurrentPlayer='', lbCurrentSubj='', lbCurrentLvl='';

function openLeaderboard(){
  lbCurrentPlayer=''; lbCurrentSubj=''; lbCurrentLvl='';
  populateLbFilters(); renderLeaderboard(); goTo('screen-leaderboard');
}

function openLeaderboardFromResult(){
  const s=subjects.find(x=>x.id===selSubjectId), l=levels.find(x=>x.id===selLevelId);
  lbCurrentPlayer=currentPlayer;
  lbCurrentSubj=s?.name||'';
  lbCurrentLvl=l?.name||'';
  populateLbFilters();
  setTimeout(()=>{
    const fs=document.getElementById('lb-filter-subj'),fl=document.getElementById('lb-filter-lvl');
    if(s) fs.value=s.name;
    if(l) fl.value=l.name;
    renderLeaderboard();
  },30);
  goTo('screen-leaderboard');
}

function populateLbFilters(){
  const fs=document.getElementById('lb-filter-subj'),fl=document.getElementById('lb-filter-lvl');
  fs.innerHTML='<option value="">— সব বিষয় —</option>'+subjects.map(s=>`<option value="${s.name}">${s.emoji} ${esc(s.name)}</option>`).join('');
  fl.innerHTML='<option value="">— সব Level —</option>'+levels.map(l=>`<option value="${l.name}">${esc(l.name)}</option>`).join('');
}

function renderLeaderboard(){
  const fSubj=document.getElementById('lb-filter-subj').value||null;
  const fLvl=document.getElementById('lb-filter-lvl').value||null;
  const ranked=getRankedList(fSubj,fLvl);
  const list=document.getElementById('lb-list');
  if(!ranked.length){list.innerHTML='<div class="empty-state"><div class="empty-icon">📭</div><div>এখনো কেউ কুইজ দেয়নি</div></div>';return;}
  const rankEmojis={1:'🥇',2:'🥈',3:'🥉'};
  list.innerHTML=ranked.map((p,i)=>{
    const rank=i+1;
    const rankTxt=rankEmojis[rank]||rank;
    const rankCls=rank===1?'r1':rank===2?'r2':rank===3?'r3':'rn';
    const cls=p.pct>=70?'score-high':p.pct>=40?'score-mid':'score-low';
    // highlight "me" — last quiz taker viewing from result
    const isMe=lbCurrentPlayer&&p.name===lbCurrentPlayer&&p.subject===(lbCurrentSubj)&&p.level===(lbCurrentLvl)&&p===participants[participants.length-1];
    return `<div class="lb-row ${isMe?'my-row':''}">
      <div class="lb-rank ${rankCls}">${rankTxt}</div>
      <div>
        <div class="lb-name ${isMe?'me':''}">${esc(p.name)}${isMe?'<span class="lb-you-badge">তুমি</span>':''}</div>
        ${p.school?`<div style="font-size:.72rem;color:var(--muted);margin-top:1px;">🏛️ ${esc(p.school)}</div>`:''}
      </div>
      <div style="text-align:center;font-size:.79rem;">${p.subjectEmoji||''}<span style="color:var(--muted)"> ${esc(p.subject||'')}</span></div>
      <div style="text-align:center;"><span class="score-badge ${cls}">${p.score}/${p.fullMarks}</span></div>
      <div class="lb-time">${p.timeStr||'-'}</div>
    </div>`;
  }).join('');
}


// ═══════════════ ADMIN MERIT ═══════════════

function renderAdminMerit(){
  participants=JSON.parse(localStorage.getItem('mq_participants')||'[]');
  const ms=document.getElementById('m-filter-subj'),ml=document.getElementById('m-filter-lvl');
  const prevSubj=ms.value,prevLvl=ml.value;
  ms.innerHTML='<option value="">— সব বিষয় —</option>'+subjects.map(s=>`<option value="${s.name}">${s.emoji} ${esc(s.name)}</option>`).join('');
  ml.innerHTML='<option value="">— সব Level —</option>'+levels.map(l=>`<option value="${l.name}">${esc(l.name)}</option>`).join('');
  if(prevSubj)ms.value=prevSubj;if(prevLvl)ml.value=prevLvl;
  const fSubj=ms.value||null,fLvl=ml.value||null;
  const ranked=getRankedList(fSubj,fLvl);
  document.getElementById('merit-count-badge').textContent=`${ranked.length} জন`;
  const list=document.getElementById('admin-merit-list');
  if(!ranked.length){list.innerHTML='<div class="empty-state"><div class="empty-icon">📭</div><div>কোনো result নেই</div></div>';return;}
  const re={1:'🥇',2:'🥈',3:'🥉'};
  list.innerHTML=ranked.map((p,i)=>{
    const rank=i+1;
    const rankTxt=re[rank]||rank;
    const rankCls=rank===1?'r1':rank===2?'r2':rank===3?'r3':'rn';
    const cls=p.pct>=70?'score-high':p.pct>=40?'score-mid':'score-low';
    return `<div class="lb-row">
      <div class="lb-rank ${rankCls}">${rankTxt}</div>
      <div>
        <div class="lb-name">${esc(p.name)}</div>
        ${p.school?`<div style="font-size:.72rem;color:var(--muted);margin-top:1px;">🏛️ ${esc(p.school)}</div>`:''}
      </div>
      <div style="text-align:center;font-size:.79rem;">${p.subjectEmoji||''}<span style="color:var(--muted)"> ${esc(p.subject||'')} · ${esc(p.levelShort||p.level||'')}</span></div>
      <div style="text-align:center;"><span class="score-badge ${cls}">${p.score}/${p.fullMarks} (${p.pct}%)</span></div>
      <div class="lb-time">${p.timeStr||'-'}</div>
    </div>`;
  }).join('');
}


// ═══════════════ ADMIN ═══════════════

function adminLogin(){
  if(document.getElementById('admin-pass').value===ADMIN_PASSWORD){
    document.getElementById('admin-pass').value='';
    document.getElementById('admin-error').textContent='';
    loadResults();renderAdminMerit();renderSubjList();renderLvlList();renderQList();
    loadSettingsUI(); loadImportUI();
    goTo('screen-admin');
  }else document.getElementById('admin-error').textContent='❌ পাসওয়ার্ড ভুল!';
}

function adminLogout(){goTo('screen-home');}

function switchTab(id,btn){
  document.querySelectorAll('.tab-content').forEach(t=>t.classList.remove('active'));
  document.querySelectorAll('.tab-btn').forEach(b=>b.classList.remove('active'));
  document.getElementById(id).classList.add('active');btn.classList.add('active');
  if(id==='tab-results')loadResults();
  if(id==='tab-merit')renderAdminMerit();
  if(id==='tab-subjects')renderSubjList();
  if(id==='tab-levels')renderLvlList();
  if(id==='tab-questions')renderQList();
  if(id==='tab-settings')loadSettingsUI();
  if(id==='tab-import')loadImportUI();
}

// RESULTS

function loadResults(){
  participants=JSON.parse(localStorage.getItem('mq_participants')||'[]');
  // populate filters
  const rs=document.getElementById('r-filter-subj');
  const rv=rs.value;
  rs.innerHTML='<option value="">— সব বিষয় —</option>'+subjects.map(s=>`<option value="${s.id}">${s.emoji} ${esc(s.name)}</option>`).join('');
  rs.value=rv;
  const rl=document.getElementById('r-filter-lvl');
  const rlv=rl.value;
  rl.innerHTML='<option value="">— সব Level —</option>'+levels.map(l=>`<option value="${l.id}">${esc(l.name)}</option>`).join('');
  rl.value=rlv;

  const fSubj=rs.value?parseInt(rs.value):null;
  const fLvl=rl.value?parseInt(rl.value):null;
  let filtered=[...participants];
  if(fSubj) filtered=filtered.filter(p=>p.subject===subjects.find(s=>s.id===fSubj)?.name);
  if(fLvl)  filtered=filtered.filter(p=>p.level===levels.find(l=>l.id===fLvl)?.name);
  const sorted=filtered.sort((a,b)=>b.score-a.score||a.timeSec-b.timeSec);

  document.getElementById('stat-total').textContent=sorted.length;
  if(sorted.length){
    document.getElementById('stat-avg').textContent=Math.round(sorted.reduce((s,p)=>s+p.pct,0)/sorted.length)+'%';
    document.getElementById('stat-top').textContent=Math.max(...sorted.map(p=>p.score))+'/'+sorted[0].fullMarks;
  }else{document.getElementById('stat-avg').textContent='-';document.getElementById('stat-top').textContent='-';}

  const list=document.getElementById('participants-list');
  if(!sorted.length){list.innerHTML='<div class="empty-state"><div class="empty-icon">📭</div><div>কোনো Result নেই</div></div>';return;}
  const re=['🥇','🥈','🥉'],rc=['top1','top2','top3'];
  list.innerHTML=sorted.map((p,i)=>{
    const cls=p.pct>=70?'score-high':p.pct>=40?'score-mid':'score-low';
    return `<div class="tbl-row">
      <div class="rank ${i<3?rc[i]:''}">${i<3?re[i]:i+1}</div>
      <div>
        <div class="p-name">${esc(p.name)}</div>
        ${p.school?`<div style="font-size:.72rem;color:var(--muted);margin-top:1px;">🏛️ ${esc(p.school)}</div>`:''}
      </div>
      <div>${p.subjectEmoji||''} <span style="font-size:.74rem;color:var(--muted)">${esc(p.subject||'')}</span></div>
      <div><span class="lvl-chip">${esc(p.levelShort||p.level||'')}</span></div>
      <div><span class="score-badge ${cls}">${p.score}/${p.fullMarks} (${p.pct}%)</span></div>
      <div class="time-col">${p.timeStr||'-'}</div>
    </div>`;
  }).join('');
}

function clearResults(){
  if(confirm('সব Result মুছে ফেলবো?')){participants=[];sv('mq_participants',participants);loadResults();showToast('🗑️ মুছা হয়েছে','wrong-t');}
}

// SUBJECTS

function renderSubjList(){
  const list=document.getElementById('subj-list');
  if(!subjects.length){list.innerHTML='<div class="empty-state"><div class="empty-icon">📂</div><div>কোনো বিষয় নেই।</div></div>';return;}
  list.innerHTML=subjects.map(s=>{
    const cnt=questions.filter(q=>q.subjectId===s.id).length;
    return `<div class="subj-item">
      <div class="subj-item-left"><div class="subj-emoji">${s.emoji}</div>
        <div><div class="subj-item-name" style="color:${s.color}">${esc(s.name)}</div><div class="subj-item-count">${cnt} টি প্রশ্ন</div></div>
      </div>
      <div class="subj-item-actions">
        <button class="btn btn-blue btn-sm" onclick="openSubjModal(${s.id})">✏️</button>
        <button class="btn btn-outline btn-sm" style="color:var(--accent2);border-color:var(--accent2);" onclick="deleteSubject(${s.id})">🗑️</button>
      </div>
    </div>`;
  }).join('');
}
const EMOJIS=['🧮','📐','🔬','⚗️','🧪','🌍','📖','🖊️','🧬','💡','🔭','📊','🏛️','🌿','🩺','💻','🎨','🎵','⚽','🌏','🧑‍🔬','📝','🔢','🏫','🎓'];

function openSubjModal(id=null){
  editingSubjId=id;
  document.getElementById('subj-modal-error').textContent='';
  document.getElementById('subj-modal-title').textContent=id?'বিষয় সম্পাদনা':'নতুন বিষয়';
  const grid=document.getElementById('subj-emoji-grid');
  grid.innerHTML=EMOJIS.map(e=>`<span class="emoji-opt" onclick="pickEmoji('${e}')">${e}</span>`).join('');
  if(id){const s=subjects.find(x=>x.id===id);document.getElementById('sm-name').value=s.name;document.getElementById('sm-color').value=s.color;selEmoji=s.emoji;}
  else{document.getElementById('sm-name').value='';document.getElementById('sm-color').value='#f7c948';selEmoji='🧮';}
  highlightEmoji(); document.getElementById('subj-modal').classList.add('open');
}

function pickEmoji(e){selEmoji=e;highlightEmoji();}

function highlightEmoji(){document.querySelectorAll('.emoji-opt').forEach(el=>el.classList.toggle('active',el.textContent===selEmoji));}

function closeSubjModal(){document.getElementById('subj-modal').classList.remove('open');}

function saveSubject(){
  const name=document.getElementById('sm-name').value.trim(),color=document.getElementById('sm-color').value;
  if(!name){document.getElementById('subj-modal-error').textContent='⚠️ নাম লিখুন!';return;}
  if(editingSubjId){const idx=subjects.findIndex(x=>x.id===editingSubjId);subjects[idx]={...subjects[idx],name,emoji:selEmoji,color};showToast('✅ আপডেট হয়েছে!','correct-t');}
  else{subjects.push({id:nid(subjects),name,emoji:selEmoji,color});showToast('✅ যোগ হয়েছে!','correct-t');}
  sv('mq_subjects',subjects);closeSubjModal();renderSubjList();
}

function deleteSubject(id){
  const cnt=questions.filter(q=>q.subjectId===id).length;
  if(!confirm(`এই বিষয় ও ${cnt}টি প্রশ্ন মুছবো?`))return;
  subjects=subjects.filter(s=>s.id!==id);questions=questions.filter(q=>q.subjectId!==id);
  sv('mq_subjects',subjects);sv('mq_questions',questions);renderSubjList();renderQList();showToast('🗑️ মুছা হয়েছে','wrong-t');
}

// LEVELS

function renderLvlList(){
  const list=document.getElementById('lvl-list');
  if(!levels.length){list.innerHTML='<div class="empty-state"><div class="empty-icon">🏫</div><div>কোনো Level নেই।</div></div>';return;}
  list.innerHTML=levels.map(l=>{
    const cnt=questions.filter(q=>q.levelId===l.id).length;
    return `<div class="lvl-item">
      <div class="lvl-item-left">
        <div class="lvl-badge-big">${esc(l.short||l.name)}</div>
        <div><div style="font-weight:600;font-size:.93rem;">${esc(l.name)}</div><div class="lvl-item-count">${cnt} টি প্রশ্ন</div></div>
      </div>
      <div class="lvl-item-actions">
        <button class="btn btn-blue btn-sm" onclick="openLvlModal(${l.id})">✏️</button>
        <button class="btn btn-outline btn-sm" style="color:var(--accent2);border-color:var(--accent2);" onclick="deleteLevel(${l.id})">🗑️</button>
      </div>
    </div>`;
  }).join('');
}

function openLvlModal(id=null){
  editingLvlId=id;
  document.getElementById('lvl-modal-error').textContent='';
  document.getElementById('lvl-modal-title').textContent=id?'Level সম্পাদনা':'নতুন Level';
  if(id){const l=levels.find(x=>x.id===id);document.getElementById('lm-name').value=l.name;document.getElementById('lm-short').value=l.short||'';}
  else{document.getElementById('lm-name').value='';document.getElementById('lm-short').value='';}
  document.getElementById('lvl-modal').classList.add('open');
}

function closeLvlModal(){document.getElementById('lvl-modal').classList.remove('open');}

function saveLevel(){
  const name=document.getElementById('lm-name').value.trim(),short=document.getElementById('lm-short').value.trim();
  if(!name){document.getElementById('lvl-modal-error').textContent='⚠️ নাম লিখুন!';return;}
  if(editingLvlId){const idx=levels.findIndex(x=>x.id===editingLvlId);levels[idx]={...levels[idx],name,short};showToast('✅ আপডেট হয়েছে!','correct-t');}
  else{levels.push({id:nid(levels),name,short});showToast('✅ যোগ হয়েছে!','correct-t');}
  sv('mq_levels',levels);closeLvlModal();renderLvlList();
}

function deleteLevel(id){
  const cnt=questions.filter(q=>q.levelId===id).length;
  if(!confirm(`এই Level ও ${cnt}টি প্রশ্ন মুছবো?`))return;
  levels=levels.filter(l=>l.id!==id);questions=questions.filter(q=>q.levelId!==id);
  sv('mq_levels',levels);sv('mq_questions',questions);renderLvlList();renderQList();showToast('🗑️ মুছা হয়েছে','wrong-t');
}

// QUESTIONS

function renderQList(){
  const fs=document.getElementById('q-filter-subj'),fl=document.getElementById('q-filter-lvl');
  const prevSubj=fs.value,prevLvl=fl.value;
  fs.innerHTML='<option value="">— সব বিষয় —</option>'+subjects.map(s=>`<option value="${s.id}">${s.emoji} ${esc(s.name)}</option>`).join('');
  fl.innerHTML='<option value="">— সব Level —</option>'+levels.map(l=>`<option value="${l.id}">${esc(l.name)}</option>`).join('');
  if(prevSubj)fs.value=prevSubj;if(prevLvl)fl.value=prevLvl;
  const fSubj=fs.value?parseInt(fs.value):null,fLvl=fl.value?parseInt(fl.value):null;
  let filtered=questions;
  if(fSubj)filtered=filtered.filter(q=>q.subjectId===fSubj);
  if(fLvl) filtered=filtered.filter(q=>q.levelId===fLvl);
  document.getElementById('q-count-badge').textContent=`${filtered.length} টি প্রশ্ন`;
  const list=document.getElementById('q-list');
  if(!filtered.length){list.innerHTML='<div class="empty-state"><div class="empty-icon">📝</div><div>কোনো প্রশ্ন নেই।</div></div>';return;}
  const letters=['ক','খ','গ','ঘ'];
  list.innerHTML=filtered.map((q,i)=>{
    const s=subjects.find(x=>x.id===q.subjectId),l=levels.find(x=>x.id===q.levelId);
    const marks=q.marks||1;
    const tagsHtml=q.tags&&q.tags.length?q.tags.map(t=>`<span style="background:rgba(167,139,250,.1);border:1px solid rgba(167,139,250,.3);color:var(--purple);border-radius:20px;padding:1px 6px;font-size:.68rem;">#${esc(t)}</span>`).join(''):'';
    return `<div class="q-item">
      <div class="q-item-top">
        <div class="q-item-text">${esc(q.q)}${q.image?` <span style="font-size:.75rem;color:var(--blue);">🖼️</span>`:''}${q.explanation?` <span style="font-size:.75rem;color:var(--green);">💡</span>`:''}${q.wordLinks&&q.wordLinks.length?` <span style="font-size:.75rem;color:var(--blue);">🔗 ${q.wordLinks.length}টি link</span>`:''}</div>
        <div class="q-item-meta">
          <span class="q-item-num">#${i+1}</span>
          <span class="${marks>1?'mark-badge-custom':'mark-chip'}">${marks} নম্বর</span>
          ${s?`<span class="q-opt-chip" style="border-color:${s.color}40;color:${s.color}">${s.emoji} ${esc(s.name)}</span>`:''}
          ${l?`<span class="lvl-chip">${esc(l.short||l.name)}</span>`:''}
        </div>
      </div>
      ${q.context?`<div style="font-size:.76rem;color:var(--blue);margin-top:4px;">📌 ${esc(q.context)}</div>`:''}
      ${tagsHtml?`<div style="display:flex;gap:4px;flex-wrap:wrap;margin-top:5px;">${tagsHtml}</div>`:''}
      <div class="q-item-opts">${q.opts.map((o,oi)=>`<span class="q-opt-chip ${oi===q.ans?'correct-chip':''}">${letters[oi]}) ${esc(o)}</span>`).join('')}</div>
      <div class="q-item-actions">
        <button class="btn btn-blue btn-sm" onclick="openQModal(${q.id})">✏️ সম্পাদনা</button>
        <button class="btn btn-outline btn-sm" style="color:var(--accent2);border-color:var(--accent2);" onclick="deleteQuestion(${q.id})">🗑️ মুছুন</button>
      </div>
    </div>`;
  }).join('');
}

function openQModal(id=null){
  editingQId=id;
  currentTags=[];
  currentWordLinks=[];
  document.getElementById('q-modal-error').textContent='';
  document.getElementById('q-modal-title').textContent=id?'প্রশ্ন সম্পাদনা':'নতুন প্রশ্ন';
  const ms=document.getElementById('m-subject'),ml=document.getElementById('m-level');
  ms.innerHTML=subjects.map(s=>`<option value="${s.id}">${s.emoji} ${esc(s.name)}</option>`).join('');
  ml.innerHTML=levels.map(l=>`<option value="${l.id}">${esc(l.name)}</option>`).join('');
  if(id){
    const q=questions.find(x=>x.id===id);
    ms.value=q.subjectId;ml.value=q.levelId;
    document.getElementById('m-context').value=q.context||'';
    document.getElementById('m-marks').value=q.marks||1;
    document.getElementById('m-image').value=q.image||'';
    document.getElementById('m-image-file').value='';
    // Show image info label for existing base64 images
    const imgInfo = document.getElementById('q-img-info');
    if(q.image && q.image.startsWith('data:')){
      imgInfo.textContent = '📁 আপলোড করা ছবি (সংরক্ষিত)';
    } else if(q.image){
      imgInfo.textContent = '🔗 URL থেকে ছবি';
    } else {
      imgInfo.textContent = '';
    }
    document.getElementById('m-explanation').value=q.explanation||'';
    currentTags=q.tags?[...q.tags]:[];
    currentWordLinks=q.wordLinks?JSON.parse(JSON.stringify(q.wordLinks)):[];
    ['m-opt0','m-opt1','m-opt2','m-opt3'].forEach((el,i)=>document.getElementById(el).value=q.opts[i]||'');
    document.querySelectorAll('.correct-radio').forEach(r=>r.checked=parseInt(r.value)===q.ans);
    // Load question text into editor
    setEditorText(q.q);
  }else{
    if(subjects.length)ms.value=subjects[0].id;
    if(levels.length)ml.value=levels[0].id;
    document.getElementById('m-context').value='';
    document.getElementById('m-marks').value=1;
    document.getElementById('m-image').value='';
    document.getElementById('m-image-file').value='';
    document.getElementById('q-img-info').textContent='';
    document.getElementById('m-explanation').value='';
    currentTags=[];
    currentWordLinks=[];
    ['m-opt0','m-opt1','m-opt2','m-opt3'].forEach(el=>document.getElementById(el).value='');
    document.querySelectorAll('.correct-radio').forEach(r=>r.checked=false);
    setEditorText('');
  }
  renderTagChips();
  renderWlList();
  previewQImage();
  document.getElementById('q-modal').classList.add('open');
}

function closeQModal(){document.getElementById('q-modal').classList.remove('open');closeWlToolbar();}

// TAG INPUT

function handleTagInput(e){
  if(e.key==='Enter'||e.key===','){
    e.preventDefault();
    const val=e.target.value.trim().replace(/,/g,'');
    if(val&&!currentTags.includes(val)){currentTags.push(val);renderTagChips();}
    e.target.value='';
  }else if(e.key==='Backspace'&&!e.target.value&&currentTags.length){
    currentTags.pop();renderTagChips();
  }
}

function renderTagChips(){
  const wrap=document.getElementById('tag-input-wrap');
  if(!wrap)return;
  const oldChips=wrap.querySelectorAll('.tag-chip');
  oldChips.forEach(c=>c.remove());
  const inp=document.getElementById('tag-real-input');
  currentTags.forEach((t,i)=>{
    const chip=document.createElement('span');
    chip.className='tag-chip';
    chip.innerHTML=`${esc(t)}<span class="tag-chip-x" onclick="removeTag(${i})">×</span>`;
    wrap.insertBefore(chip,inp);
  });
}

function removeTag(i){currentTags.splice(i,1);renderTagChips();}

// IMAGE PREVIEW & UPLOAD

function previewQImage(){
  const url=document.getElementById('m-image').value.trim();
  const wrap=document.getElementById('q-img-preview');
  const img=document.getElementById('q-img-preview-el');
  const info=document.getElementById('q-img-info');
  if(url){
    wrap.style.display='block';
    img.src=url;
    img.onerror=()=>wrap.style.display='none';
    // Show URL source indicator
    if(!url.startsWith('data:')){
      info.textContent='🔗 URL থেকে ছবি';
    }
  } else {
    wrap.style.display='none';
  }
}


function handleImageFileUpload(input){
  const file = input.files[0];
  if(!file) return;

  // Max size check: 2MB (base64 will be ~33% larger, stored in localStorage)
  if(file.size > 2 * 1024 * 1024){
    showToast('⚠️ ছবির সাইজ সর্বোচ্চ ২MB হতে হবে!', 'wrong-t');
    input.value = '';
    return;
  }

  const reader = new FileReader();
  reader.onload = function(e){
    const base64 = e.target.result; // data:image/jpeg;base64,...
    document.getElementById('m-image').value = base64;

    const wrap = document.getElementById('q-img-preview');
    const img = document.getElementById('q-img-preview-el');
    const info = document.getElementById('q-img-info');
    wrap.style.display = 'block';
    img.src = base64;
    const kb = Math.round(file.size / 1024);
    info.textContent = `📁 ${file.name} · ${kb} KB`;
    showToast('✅ ছবি upload হয়েছে!', 'correct-t');
  };
  reader.onerror = () => showToast('❌ ছবি পড়তে সমস্যা হয়েছে!', 'wrong-t');
  reader.readAsDataURL(file);
}


function clearQImage(){
  document.getElementById('m-image').value = '';
  document.getElementById('m-image-file').value = '';
  document.getElementById('q-img-preview').style.display = 'none';
  document.getElementById('q-img-preview-el').src = '';
  document.getElementById('q-img-info').textContent = '';
  showToast('🗑️ ছবি মুছা হয়েছে', 'wrong-t');
}


function saveQuestion(){
  const qText=document.getElementById('m-question').value.trim();
  const opts=['m-opt0','m-opt1','m-opt2','m-opt3'].map(id=>document.getElementById(id).value.trim());
  const correctEl=document.querySelector('.correct-radio:checked');
  const subjId=parseInt(document.getElementById('m-subject').value);
  const lvlId=parseInt(document.getElementById('m-level').value);
  const marks=parseInt(document.getElementById('m-marks').value)||1;
  const image=document.getElementById('m-image').value.trim();
  const explanation=document.getElementById('m-explanation').value.trim();
  const err=document.getElementById('q-modal-error');
  if(!qText){err.textContent='⚠️ প্রশ্ন লিখুন!';return;}
  if(opts.some(o=>!o)){err.textContent='⚠️ সবগুলো বিকল্প লিখুন!';return;}
  if(!correctEl){err.textContent='⚠️ সঠিক উত্তর select করুন!';return;}
  const ctx=document.getElementById('m-context').value.trim();
  const validWordLinks=currentWordLinks.filter(wl=>qText.includes(wl.word));
  const nq={id:editingQId||nid(questions),subjectId:subjId,levelId:lvlId,q:qText,opts,ans:parseInt(correctEl.value),marks,...(ctx&&{context:ctx}),...(image&&{image}),...(explanation&&{explanation}),...(currentTags.length&&{tags:[...currentTags]}),...(validWordLinks.length&&{wordLinks:validWordLinks})};
  if(editingQId){const idx=questions.findIndex(x=>x.id===editingQId);questions[idx]=nq;showToast('✅ আপডেট!','correct-t');}
  else{questions.push(nq);showToast('✅ যোগ হয়েছে!','correct-t');}
  sv('mq_questions',questions);closeQModal();renderQList();
}

function deleteQuestion(id){
  if(!confirm('এই প্রশ্ন মুছবো?'))return;
  questions=questions.filter(q=>q.id!==id);sv('mq_questions',questions);renderQList();showToast('🗑️ মুছা হয়েছে','wrong-t');
}

// modal close on overlay click
['q-modal','subj-modal','lvl-modal'].forEach(id=>{
  document.getElementById(id).addEventListener('click',function(e){if(e.target===this)this.classList.remove('open');});
});

// home quiz button
document.getElementById('btn-home-quiz').onclick=()=>{renderSubjectGrid();goTo('screen-select-subject');};

// TOAST

function showToast(msg,cls){
  const t=document.getElementById('toast');t.textContent=msg;t.className='toast '+cls+' show';
  clearTimeout(t._t);t._t=setTimeout(()=>t.classList.remove('show'),2200);
}


// ═══════════════ SETTINGS ═══════════════

function loadSettingsUI(){
  const mins=(parseInt(localStorage.getItem('mq_timer_min'))||30);
  document.getElementById('setting-timer').value=mins;
  document.getElementById('current-timer-display').textC
