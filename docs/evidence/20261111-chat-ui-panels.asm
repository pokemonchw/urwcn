
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

00534150 <.text+0x133150>:
  534150:	51                   	push   ecx
  534151:	a1 5c ba 5b 06       	mov    eax,ds:0x65bba5c
  534156:	ba 04 00 00 00       	mov    edx,0x4
  53415b:	8b 0d 30 06 62 0a    	mov    ecx,DWORD PTR ds:0xa620630
  534161:	6a 00                	push   0x0
  534163:	6a 22                	push   0x22
  534165:	a3 b0 1c 5c 0a       	mov    ds:0xa5c1cb0,eax
  53416a:	c7 05 5c ba 5b 06 00 	mov    DWORD PTR ds:0x65bba5c,0x0
  534171:	00 00 00 
  534174:	e8 77 93 f7 ff       	call   0x4ad4f0
  534179:	50                   	push   eax
  53417a:	68 be 00 00 00       	push   0xbe
  53417f:	68 cc 01 00 00       	push   0x1cc
  534184:	ba e7 00 00 00       	mov    edx,0xe7
  534189:	b9 07 00 00 00       	mov    ecx,0x7
  53418e:	e8 dd 20 fe ff       	call   0x516270
  534193:	83 c4 14             	add    esp,0x14
  534196:	ba 80 18 5b 00       	mov    edx,0x5b1880
  53419b:	6a 01                	push   0x1
  53419d:	51                   	push   ecx
  53419e:	69 0d 30 06 62 0a 68 	imul   ecx,DWORD PTR ds:0xa620630,0x568
  5341a5:	05 00 00 
  5341a8:	68 78 18 5b 00       	push   0x5b1878
  5341ad:	81 c1 49 14 15 06    	add    ecx,0x6151449
  5341b3:	e8 58 2a fe ff       	call   0x516c10
  5341b8:	83 c4 0c             	add    esp,0xc
  5341bb:	69 c0 48 0c 00 00    	imul   eax,eax,0xc48
  5341c1:	c7 80 1c 52 78 0a 2e 	mov    DWORD PTR [eax+0xa78521c],0x12e
  5341c8:	01 00 00 
  5341cb:	c7 80 20 52 78 0a ff 	mov    DWORD PTR [eax+0xa785220],0xff
  5341d2:	00 00 00 
  5341d5:	c7 80 24 52 78 0a a0 	mov    DWORD PTR [eax+0xa785224],0xa0
  5341dc:	00 00 00 
  5341df:	c7 80 28 52 78 0a a0 	mov    DWORD PTR [eax+0xa785228],0xa0
  5341e6:	00 00 00 
  5341e9:	a1 b0 1c 5c 0a       	mov    eax,ds:0xa5c1cb0
  5341ee:	a3 5c ba 5b 06       	mov    ds:0x65bba5c,eax
  5341f3:	59                   	pop    ecx
  5341f4:	c3                   	ret
  5341f5:	cc                   	int3
  5341f6:	cc                   	int3
  5341f7:	cc                   	int3
  5341f8:	cc                   	int3
  5341f9:	cc                   	int3
  5341fa:	cc                   	int3
  5341fb:	cc                   	int3
  5341fc:	cc                   	int3
  5341fd:	cc                   	int3
  5341fe:	cc                   	int3
  5341ff:	cc                   	int3
  534200:	55                   	push   ebp
  534201:	8b ec                	mov    ebp,esp
  534203:	81 ec 08 04 00 00    	sub    esp,0x408
  534209:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  53420e:	33 c5                	xor    eax,ebp
  534210:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  534213:	a1 5c ba 5b 06       	mov    eax,ds:0x65bba5c
  534218:	ba 1f 00 00 00       	mov    edx,0x1f
  53421d:	6a 00                	push   0x0
  53421f:	6a 22                	push   0x22
  534221:	68 e8 a6 72 0a       	push   0xa72a6e8
  534226:	68 be 00 00 00       	push   0xbe
  53422b:	68 cc 01 00 00       	push   0x1cc
  534230:	8d 4a e8             	lea    ecx,[edx-0x18]
  534233:	a3 b0 1c 5c 0a       	mov    ds:0xa5c1cb0,eax
  534238:	c7 05 5c ba 5b 06 00 	mov    DWORD PTR ds:0x65bba5c,0x0
  53423f:	00 00 00 
  534242:	e8 29 20 fe ff       	call   0x516270
  534247:	83 c4 14             	add    esp,0x14
  53424a:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  534250:	68 90 3c 78 0a       	push   0xa783c90
  534255:	68 70 f4 58 00       	push   0x58f470
  53425a:	50                   	push   eax
  53425b:	e8 70 ce ec ff       	call   0x4010d0
  534260:	83 c4 0c             	add    esp,0xc
  534263:	ba 90 18 5b 00       	mov    edx,0x5b1890
  534268:	6a 01                	push   0x1
  53426a:	51                   	push   ecx
  53426b:	68 78 18 5b 00       	push   0x5b1878
  534270:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  534276:	e8 95 29 fe ff       	call   0x516c10
  53427b:	83 c4 0c             	add    esp,0xc
  53427e:	85 c0                	test   eax,eax
  534280:	78 2e                	js     0x5342b0
  534282:	69 c0 48 0c 00 00    	imul   eax,eax,0xc48
  534288:	c7 80 1c 52 78 0a 0c 	mov    DWORD PTR [eax+0xa78521c],0xc
  53428f:	00 00 00 
  534292:	c7 80 20 52 78 0a 37 	mov    DWORD PTR [eax+0xa785220],0x37
  534299:	00 00 00 
  53429c:	c7 80 24 52 78 0a a0 	mov    DWORD PTR [eax+0xa785224],0xa0
  5342a3:	00 00 00 
  5342a6:	c7 80 28 52 78 0a a0 	mov    DWORD PTR [eax+0xa785228],0xa0
  5342ad:	00 00 00 
  5342b0:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  5342b3:	33 cd                	xor    ecx,ebp
  5342b5:	e8 f4 5d 05 00       	call   0x58a0ae
  5342ba:	8b e5                	mov    esp,ebp
  5342bc:	5d                   	pop    ebp
  5342bd:	c3                   	ret
  5342be:	cc                   	int3
  5342bf:	cc                   	int3
  5342c0:	55                   	push   ebp
  5342c1:	8b ec                	mov    ebp,esp
  5342c3:	83 ec 70             	sub    esp,0x70
  5342c6:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  5342cb:	33 c5                	xor    eax,ebp
  5342cd:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  5342d0:	51                   	push   ecx
  5342d1:	68 58 02 00 00       	push   0x258
  5342d6:	68 20 03 00 00       	push   0x320
  5342db:	83 ec 08             	sub    esp,0x8
  5342de:	33 d2                	xor    edx,edx
  5342e0:	b9 c8 54 59 00       	mov    ecx,0x5954c8
  5342e5:	e8 d6 e4 fd ff       	call   0x5127c0
  5342ea:	8b 0d 30 06 62 0a    	mov    ecx,DWORD PTR ds:0xa620630
  5342f0:	83 c4 14             	add    esp,0x14
  5342f3:	ba 04 00 00 00       	mov    edx,0x4
  5342f8:	e8 f3 91 f7 ff       	call   0x4ad4f0
  5342fd:	50                   	push   eax
  5342fe:	8d 45 90             	lea    eax,[ebp-0x70]
  534301:	68 a0 18 5b 00       	push   0x5b18a0
  534306:	50                   	push   eax
  534307:	e8 c4 cd ec ff       	call   0x4010d0
  53430c:	83 c4 0c             	add    esp,0xc
  53430f:	8d 4d 90             	lea    ecx,[ebp-0x70]
  534312:	e8 69 4c fc ff       	call   0x4f8f80
  534317:	e8 e4 fe ff ff       	call   0x534200
  53431c:	e8 2f fe ff ff       	call   0x534150
  534321:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  534324:	33 cd                	xor    ecx,ebp
  534326:	e8 83 5d 05 00       	call   0x58a0ae
  53432b:	8b e5                	mov    esp,ebp
  53432d:	5d                   	pop    ebp
  53432e:	c3                   	ret
  53432f:	cc                   	int3
