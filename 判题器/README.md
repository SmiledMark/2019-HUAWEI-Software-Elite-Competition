# huawei2019
华为2019评判器开源,与线上不完全一致（map1 700时间段以内，map2 600时间段以内)    
(已经很尽力按照官方要求写了，还不一样真的不明觉厉...... :( )     
#***** 注意，比赛代码会查重，请小心使用=v=! ****#


#**** 更新 ****#    
2019/3/22  
添加了到终点车辆对其它道路车辆的影响。参考（https://bbs.huaweicloud.com/forum/thread-15362-1-1.html）

2019/3/21  
加入锁死判据：  
    在一个cross循环中，若所有cross都未更新，即锁死。cross循环指按cross id 升序遍历所有cross的过程。（注：例外，当所有cross上所有道路都更新完毕时，再一次cross循环时，所有cross是不会更新的，如起始状态。）

2019/3/20    
原代码中，车辆到达设计出发时间无法上路会导致报错。新代码做了更改，未上路的车加入下一时刻判断。  
ps:官方并未说明这里如何实现。我的原则如下例子所示：
             按照从左到右依次上路
time:10 [10001,10002,10003,10010] 10010未能上路
time：11 [10010,10004,10005,10006,10007]





#**** 判题器调度规则 ****#

(1) step 1:车道内车辆状态更新为等待状态。车道内车辆有道路出口向道路末尾依次判断车是否能运行（”道内移动“），若能运行则标记为完毕状态。（当且仅当车辆不会出路口，前前方阻拦车辆为完毕状态 或 无阻拦时 才可运行） 

(2)step 2:伪代码如下(为了方便阅读，写成易理解的形式，主要演示调度规则。我的实现做了一些处理，方便写成代码)      
time==0     
while allCarDone == False:   
    while allCrossDone == False :   
		for cross in allCross(升序):
			firstPriorityCars = []    
			for road in crossRoad:    
				firstPriorityCars.append(road.getFirstPriorityCar())    
			for road in crossRoad(升序，仅考虑在当前cross下作为出口的road):   
				car = road.getFirstPriorityCar()(仅为可能出道路的车)    
				if conflict(road,car,firstPriorityCars):    
					break  
				car.run()  
				road.run(car.channel)（一旦car到达完毕状态，road中car所在车道做一次”道内移动“）  	    
	time+=1  


conflict判断：   
（除了前方道路车辆出于等待状态以外）

0，1，2，3 分别表示 北东南西  
-1，1，2 分别表示右，左，直  
#*           0(5004)  
#*   3(5001)         1(5003)  
#*           2(5002)  


判断依据只看车辆的 ”***出道路和行驶方向***“，与是否到达终点无关（到终点行驶方向作直行）。（来自于小原解答https://bbs.huaweicloud.com/forum/thread-15362-1-1.html）

carA，roadA，dirA  carB,roadB,dirB

if(roadA+dirA)%4 == (roadB+dirB)%4 and dirA<dirB:  
    return conflict   
else:    
    return not conflict  

exp:
A,3,-1  B,0,2   
(3-1)%4==(0+2) and -1<2     
A的优先级小于B


(3)无限车库出车：按照车辆id升序出车。不能出车的下一时刻再判断，且设为最高优先级。
            



#**** 使用说明 ****#

(1)路径为官方SDK路径，代码存放与src目录下（与CodeCraft-2019.py 同目录）

(2)
除answer.txt以外均为原始文件，不要更改（我并未做注释处理）   
answer.txt格式为提交答案格式，但是注意不能有注释。    
错误样例：   
#xxxxx   
(carId,plantime,route)   
(carId,plantime,route)    
(carId,plantime,route)    
正例:    
(carId,plantime,route)   
(carId,plantime,route)   
(carId,plantime,route)   

(3)运行
python3 simulator.py ../config_11/car.txt ../config_11/road.txt ../config_11/cross.txt ../config_11/answer.txt

(4)可视化部分
请取消visualize.drawMap()的注释以启用可视化。     
class visualization 为可视化模块，输出图片所在文件夹记录在visualization.savePath，为所有时刻的车辆状况图片。    
class simulation 中有调用visualization。可注释simulation.simulate()中的 visualize.drawMap()以提高程序运行速度。    

(5)图片信息详细介绍    
参考   "介绍图片.rar"

#**** 发现问题的记得联系我 ****#
#**** 特别是规则有疑问 ****#
qq:2938830818
