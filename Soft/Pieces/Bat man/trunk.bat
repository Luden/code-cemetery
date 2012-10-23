@echo off
cls

set test_ip=74.125.87.147
set wifi=192.168.1.1

call :getip
set bilan=%ans%
rem если жпрс не подключен
if %bilan%==notfound (
	rasdial Beeline
	call :getip
	set bilan=%ans%
	if %bilan%==notfound (
		rem если жпрс нет вобще, то толку от скрипта чуть
		echo NO GPRS!
		pause
		exit
	)
)

rem проверим подключен ли вифи. если нет, то сразу будем юзать жпрс
call :is_wifi_up
if %xx%==0 goto start_proverka3



:Ethernet
	echo connection up 
	route delete 0.0.0.0 
	route add 0.0.0.0 mask 0.0.0.0 %wifi% metric 20 
	route add %test_ip% mask 255.255.255.255 %wifi% metric 10 
	goto start_proverka 

rem когда всё хорошо - просто пингуем гугл. как только пропадает в подряд три пакета - переключаемся на жпрс
:start_proverka
	echo connection OK
	set counter=0
	:proverka 
		ping -n 1 %test_ip%>nul		
		if errorlevel 1 (
			set /a counter=counter+1
			echo packet lost! %counter%
		) else (			
			set counter=0
		)
		
		if %counter%==4 goto beeline
		sleep -m 333
		goto proverka 

:beeline 
	echo connection lost
	route delete 0.0.0.0
	route add 0.0.0.0 mask 0.0.0.0 %bilan% metric 20 
	goto start_proverka2 

rem проверим, может обрыв линии вифи. если так, то будем ждать её восстановления (о котором нам скажет появление новых маршрутов в таблице)
rem ежели дело не с обрывом вифи, а с обрывом адсл - то пингуем гугл через вифи. как только пинги пошли - связь восстановилась
:start_proverka2
	echo gprs up
	call :is_wifi_up
	if %xx%==0 goto start_proverka3
	echo adsl down
	:proverka2 
		ping -n 1 %test_ip%>nul
		if errorlevel 0 (
			echo adsl up
			goto Ethernet
		)	
		goto proverka2

:start_proverka3
	echo wifi down
	:proverka3
		call :is_wifi_up
		sleep 1
		if %xx%==0 goto proverka3
	echo wifi up
	goto Ethernet

:getip
	set ans=notfound
	FOR /F "delims=: tokens=2 usebackq" %%i IN (`ipconfig`) DO (
		FOR /F "tokens=1,2,3,4 usebackq delims=. " %%j IN ('%%i') DO	(
			if %%j== 172 (
				set ans=%%j.%%k.%%l.%%m
			)
		)
	)
	echo dinamic ip: %ans%
exit /b

:is_wifi_up
	set xx=nodevice
	FOR /F "delims=: tokens=1 usebackq" %%i IN (`route print`) DO (
		FOR /F "tokens=3,1 usebackq" %%j IN ('%%i') DO (				
			if %%j==%wifi% (
				set xx=%%j
				goto asd
			)			
			if %%k==%wifi% (
				set xx=%%k
				goto asd
			)
		)
	 )

	:asd
	if %xx%==%wifi% (
		set xx=1
	) else (
		set xx=0
	)
exit /b