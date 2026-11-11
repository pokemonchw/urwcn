
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

00525240 <.text+0x124240>:
  525240:	55                   	push   ebp
  525241:	8b ec                	mov    ebp,esp
  525243:	83 ec 08             	sub    esp,0x8
  525246:	53                   	push   ebx
  525247:	56                   	push   esi
  525248:	8b 35 7c c2 58 00    	mov    esi,DWORD PTR ds:0x58c27c
  52524e:	33 db                	xor    ebx,ebx
  525250:	57                   	push   edi
  525251:	8b 3d 68 c2 58 00    	mov    edi,DWORD PTR ds:0x58c268
  525257:	89 55 fc             	mov    DWORD PTR [ebp-0x4],edx
  52525a:	89 4d f8             	mov    DWORD PTR [ebp-0x8],ecx
  52525d:	0f 1f 00             	nop    DWORD PTR [eax]
  525260:	8a c3                	mov    al,bl
  525262:	c0 e0 02             	shl    al,0x2
  525265:	6a 01                	push   0x1
  525267:	50                   	push   eax
  525268:	50                   	push   eax
  525269:	50                   	push   eax
  52526a:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  52526f:	ff 70 04             	push   DWORD PTR [eax+0x4]
  525272:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  525278:	8b 55 fc             	mov    edx,DWORD PTR [ebp-0x4]
  52527b:	83 c4 10             	add    esp,0x10
  52527e:	8b 4d f8             	mov    ecx,DWORD PTR [ebp-0x8]
  525281:	50                   	push   eax
  525282:	ff 75 08             	push   DWORD PTR [ebp+0x8]
  525285:	e8 16 93 fe ff       	call   0x50e5a0
  52528a:	83 c4 0c             	add    esp,0xc
  52528d:	83 3d 5c ba 5b 06 00 	cmp    DWORD PTR ds:0x65bba5c,0x0
  525294:	75 3e                	jne    0x5252d4
  525296:	e8 f5 5c fe ff       	call   0x50af90
  52529b:	83 3d d8 bc 5b 06 00 	cmp    DWORD PTR ds:0x65bbcd8,0x0
  5252a2:	74 17                	je     0x5252bb
  5252a4:	e8 97 ad fe ff       	call   0x510040
  5252a9:	a1 d8 bc 5b 06       	mov    eax,ds:0x65bbcd8
  5252ae:	33 c9                	xor    ecx,ecx
  5252b0:	83 f8 02             	cmp    eax,0x2
  5252b3:	0f 44 c1             	cmove  eax,ecx
  5252b6:	a3 d8 bc 5b 06       	mov    ds:0x65bbcd8,eax
  5252bb:	e8 00 61 fe ff       	call   0x50b3c0
  5252c0:	83 3d 54 1c 5c 0a 00 	cmp    DWORD PTR ds:0xa5c1c54,0x0
  5252c7:	75 0b                	jne    0x5252d4
  5252c9:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  5252cf:	ff d6                	call   esi
  5252d1:	83 c4 04             	add    esp,0x4
  5252d4:	6a 02                	push   0x2
  5252d6:	ff d7                	call   edi
  5252d8:	43                   	inc    ebx
  5252d9:	83 c4 04             	add    esp,0x4
  5252dc:	83 fb 3f             	cmp    ebx,0x3f
  5252df:	0f 8c 7b ff ff ff    	jl     0x525260
  5252e5:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  5252ea:	6a 01                	push   0x1
  5252ec:	6a 54                	push   0x54
  5252ee:	68 fc 00 00 00       	push   0xfc
  5252f3:	68 fc 00 00 00       	push   0xfc
  5252f8:	ff 70 04             	push   DWORD PTR [eax+0x4]
  5252fb:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  525301:	8b 55 fc             	mov    edx,DWORD PTR [ebp-0x4]
  525304:	83 c4 10             	add    esp,0x10
  525307:	8b 4d f8             	mov    ecx,DWORD PTR [ebp-0x8]
  52530a:	50                   	push   eax
  52530b:	ff 75 08             	push   DWORD PTR [ebp+0x8]
  52530e:	e8 8d 92 fe ff       	call   0x50e5a0
  525313:	83 c4 0c             	add    esp,0xc
  525316:	83 3d 5c ba 5b 06 00 	cmp    DWORD PTR ds:0x65bba5c,0x0
  52531d:	75 3e                	jne    0x52535d
  52531f:	e8 6c 5c fe ff       	call   0x50af90
  525324:	83 3d d8 bc 5b 06 00 	cmp    DWORD PTR ds:0x65bbcd8,0x0
  52532b:	74 17                	je     0x525344
  52532d:	e8 0e ad fe ff       	call   0x510040
  525332:	a1 d8 bc 5b 06       	mov    eax,ds:0x65bbcd8
  525337:	33 c9                	xor    ecx,ecx
  525339:	83 f8 02             	cmp    eax,0x2
  52533c:	0f 44 c1             	cmove  eax,ecx
  52533f:	a3 d8 bc 5b 06       	mov    ds:0x65bbcd8,eax
  525344:	e8 77 60 fe ff       	call   0x50b3c0
  525349:	83 3d 54 1c 5c 0a 00 	cmp    DWORD PTR ds:0xa5c1c54,0x0
  525350:	75 0b                	jne    0x52535d
  525352:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  525358:	ff d6                	call   esi
  52535a:	83 c4 04             	add    esp,0x4
  52535d:	5f                   	pop    edi
  52535e:	5e                   	pop    esi
  52535f:	5b                   	pop    ebx
  525360:	8b e5                	mov    esp,ebp
  525362:	5d                   	pop    ebp
  525363:	c3                   	ret
  525364:	cc                   	int3
  525365:	cc                   	int3
  525366:	cc                   	int3
  525367:	cc                   	int3
  525368:	cc                   	int3
  525369:	cc                   	int3
  52536a:	cc                   	int3
  52536b:	cc                   	int3
  52536c:	cc                   	int3
  52536d:	cc                   	int3
  52536e:	cc                   	int3
  52536f:	cc                   	int3
  525370:	55                   	push   ebp
  525371:	8b ec                	mov    ebp,esp
  525373:	81 ec a4 00 00 00    	sub    esp,0xa4
  525379:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  52537e:	33 c5                	xor    eax,ebp
  525380:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  525383:	53                   	push   ebx
  525384:	8b 1d 80 c2 58 00    	mov    ebx,DWORD PTR ds:0x58c280
  52538a:	56                   	push   esi
  52538b:	be 90 01 00 00       	mov    esi,0x190
  525390:	c7 85 64 ff ff ff 90 	mov    DWORD PTR [ebp-0x9c],0x5afd90
  525397:	fd 5a 00 
  52539a:	57                   	push   edi
  52539b:	89 b5 60 ff ff ff    	mov    DWORD PTR [ebp-0xa0],esi
  5253a1:	33 ff                	xor    edi,edi
  5253a3:	c7 85 68 ff ff ff d8 	mov    DWORD PTR [ebp-0x98],0x5afdd8
  5253aa:	fd 5a 00 
  5253ad:	c7 85 6c ff ff ff 10 	mov    DWORD PTR [ebp-0x94],0x5afe10
  5253b4:	fe 5a 00 
  5253b7:	c7 85 70 ff ff ff 58 	mov    DWORD PTR [ebp-0x90],0x5afe58
  5253be:	fe 5a 00 
  5253c1:	c7 85 74 ff ff ff a8 	mov    DWORD PTR [ebp-0x8c],0x5afea8
  5253c8:	fe 5a 00 
  5253cb:	c7 85 78 ff ff ff ec 	mov    DWORD PTR [ebp-0x88],0x5afeec
  5253d2:	fe 5a 00 
  5253d5:	c7 85 7c ff ff ff 14 	mov    DWORD PTR [ebp-0x84],0x5aff14
  5253dc:	ff 5a 00 
  5253df:	c7 45 80 34 ff 5a 00 	mov    DWORD PTR [ebp-0x80],0x5aff34
  5253e6:	c7 45 84 64 ff 5a 00 	mov    DWORD PTR [ebp-0x7c],0x5aff64
  5253ed:	c7 45 88 90 ff 5a 00 	mov    DWORD PTR [ebp-0x78],0x5aff90
  5253f4:	c7 45 8c d8 ff 5a 00 	mov    DWORD PTR [ebp-0x74],0x5affd8
  5253fb:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  525400:	8b 84 bd 64 ff ff ff 	mov    eax,DWORD PTR [ebp+edi*4-0x9c]
  525407:	8d 55 90             	lea    edx,[ebp-0x70]
  52540a:	2b d0                	sub    edx,eax
  52540c:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  525410:	8a 08                	mov    cl,BYTE PTR [eax]
  525412:	8d 40 01             	lea    eax,[eax+0x1]
  525415:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  525419:	84 c9                	test   cl,cl
  52541b:	75 f3                	jne    0x525410
  52541d:	8d 4d 90             	lea    ecx,[ebp-0x70]
  525420:	8d 51 01             	lea    edx,[ecx+0x1]
  525423:	8a 01                	mov    al,BYTE PTR [ecx]
  525425:	41                   	inc    ecx
  525426:	84 c0                	test   al,al
  525428:	75 f9                	jne    0x525423
  52542a:	2b ca                	sub    ecx,edx
  52542c:	8d 45 90             	lea    eax,[ebp-0x70]
  52542f:	50                   	push   eax
  525430:	8d 04 cd 00 00 00 00 	lea    eax,[ecx*8+0x0]
  525437:	b9 90 01 00 00       	mov    ecx,0x190
  52543c:	99                   	cdq
  52543d:	2b c2                	sub    eax,edx
  52543f:	8b d6                	mov    edx,esi
  525441:	d1 f8                	sar    eax,1
  525443:	2b c8                	sub    ecx,eax
  525445:	e8 f6 fd ff ff       	call   0x525240
  52544a:	83 c4 04             	add    esp,0x4
  52544d:	ff d3                	call   ebx
  52544f:	8b f0                	mov    esi,eax
  525451:	e8 8a d1 fa ff       	call   0x4d25e0
  525456:	85 c0                	test   eax,eax
  525458:	75 1a                	jne    0x525474
  52545a:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  525460:	ff d3                	call   ebx
  525462:	2b c6                	sub    eax,esi
  525464:	3d b8 0b 00 00       	cmp    eax,0xbb8
  525469:	7f 1c                	jg     0x525487
  52546b:	e8 70 d1 fa ff       	call   0x4d25e0
  525470:	85 c0                	test   eax,eax
  525472:	74 ec                	je     0x525460
  525474:	33 c0                	xor    eax,eax
  525476:	5f                   	pop    edi
  525477:	5e                   	pop    esi
  525478:	5b                   	pop    ebx
  525479:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  52547c:	33 cd                	xor    ecx,ebp
  52547e:	e8 2b 4c 06 00       	call   0x58a0ae
  525483:	8b e5                	mov    esp,ebp
  525485:	5d                   	pop    ebp
  525486:	c3                   	ret
  525487:	8b b5 60 ff ff ff    	mov    esi,DWORD PTR [ebp-0xa0]
  52548d:	47                   	inc    edi
  52548e:	83 c6 0a             	add    esi,0xa
  525491:	89 b5 60 ff ff ff    	mov    DWORD PTR [ebp-0xa0],esi
  525497:	83 ff 0b             	cmp    edi,0xb
  52549a:	0f 8c 60 ff ff ff    	jl     0x525400
  5254a0:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  5254a3:	b8 01 00 00 00       	mov    eax,0x1
  5254a8:	5f                   	pop    edi
  5254a9:	5e                   	pop    esi
  5254aa:	33 cd                	xor    ecx,ebp
  5254ac:	5b                   	pop    ebx
  5254ad:	e8 fc 4b 06 00       	call   0x58a0ae
  5254b2:	8b e5                	mov    esp,ebp
  5254b4:	5d                   	pop    ebp
  5254b5:	c3                   	ret
  5254b6:	cc                   	int3
  5254b7:	cc                   	int3
  5254b8:	cc                   	int3
  5254b9:	cc                   	int3
  5254ba:	cc                   	int3
  5254bb:	cc                   	int3
  5254bc:	cc                   	int3
  5254bd:	cc                   	int3
  5254be:	cc                   	int3
  5254bf:	cc                   	int3
