
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

005431d0 <.text+0x1421d0>:
  5431d0:	55                   	push   ebp
  5431d1:	8b ec                	mov    ebp,esp
  5431d3:	81 ec 0c 04 00 00    	sub    esp,0x40c
  5431d9:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  5431de:	33 c5                	xor    eax,ebp
  5431e0:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  5431e3:	56                   	push   esi
  5431e4:	ba 06 00 00 00       	mov    edx,0x6
  5431e9:	8b f1                	mov    esi,ecx
  5431eb:	e8 00 a3 f6 ff       	call   0x4ad4f0
  5431f0:	50                   	push   eax
  5431f1:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  5431f7:	68 b4 62 5b 00       	push   0x5b62b4
  5431fc:	50                   	push   eax
  5431fd:	e8 ce de eb ff       	call   0x4010d0
  543202:	83 c4 0c             	add    esp,0xc
  543205:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  54320b:	e8 00 33 fb ff       	call   0x4f6510
  543210:	b9 d4 62 5b 00       	mov    ecx,0x5b62d4
  543215:	e8 f6 32 fb ff       	call   0x4f6510
  54321a:	ba 0f 00 00 00       	mov    edx,0xf
  54321f:	33 c9                	xor    ecx,ecx
  543221:	e8 8a c3 fc ff       	call   0x50f5b0
  543226:	8d 95 f8 fb ff ff    	lea    edx,[ebp-0x408]
  54322c:	2b d0                	sub    edx,eax
  54322e:	66 90                	xchg   ax,ax
  543230:	8a 08                	mov    cl,BYTE PTR [eax]
  543232:	8d 40 01             	lea    eax,[eax+0x1]
  543235:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  543239:	84 c9                	test   cl,cl
  54323b:	75 f3                	jne    0x543230
  54323d:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  543243:	8d 51 01             	lea    edx,[ecx+0x1]
  543246:	8a 01                	mov    al,BYTE PTR [ecx]
  543248:	41                   	inc    ecx
  543249:	84 c0                	test   al,al
  54324b:	75 f9                	jne    0x543246
  54324d:	2b ca                	sub    ecx,edx
  54324f:	74 59                	je     0x5432aa
  543251:	80 bd f8 fb ff ff 1b 	cmp    BYTE PTR [ebp-0x408],0x1b
  543258:	74 50                	je     0x5432aa
  54325a:	69 ce 68 05 00 00    	imul   ecx,esi,0x568
  543260:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  543266:	80 89 dc 15 15 06 03 	or     BYTE PTR [ecx+0x61515dc],0x3
  54326d:	8d 91 30 14 15 06    	lea    edx,[ecx+0x6151430]
  543273:	8b c8                	mov    ecx,eax
  543275:	2b d1                	sub    edx,ecx
  543277:	8a 08                	mov    cl,BYTE PTR [eax]
  543279:	8d 40 01             	lea    eax,[eax+0x1]
  54327c:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  543280:	84 c9                	test   cl,cl
  543282:	75 f3                	jne    0x543277
  543284:	b9 10 1a 59 00       	mov    ecx,0x591a10
  543289:	89 35 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,esi
  54328f:	e8 6c e8 01 00       	call   0x561b00
  543294:	8b c8                	mov    ecx,eax
  543296:	e8 75 32 fb ff       	call   0x4f6510
  54329b:	5e                   	pop    esi
  54329c:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  54329f:	33 cd                	xor    ecx,ebp
  5432a1:	e8 08 6e 04 00       	call   0x58a0ae
  5432a6:	8b e5                	mov    esp,ebp
  5432a8:	5d                   	pop    ebp
  5432a9:	c3                   	ret
  5432aa:	b9 f0 5e 59 00       	mov    ecx,0x595ef0
  5432af:	e8 5c 32 fb ff       	call   0x4f6510
  5432b4:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  5432b7:	33 cd                	xor    ecx,ebp
  5432b9:	5e                   	pop    esi
  5432ba:	e8 ef 6d 04 00       	call   0x58a0ae
  5432bf:	8b e5                	mov    esp,ebp
  5432c1:	5d                   	pop    ebp
  5432c2:	c3                   	ret
  5432c3:	cc                   	int3
  5432c4:	cc                   	int3
  5432c5:	cc                   	int3
  5432c6:	cc                   	int3
  5432c7:	cc                   	int3
  5432c8:	cc                   	int3
  5432c9:	cc                   	int3
  5432ca:	cc                   	int3
  5432cb:	cc                   	int3
  5432cc:	cc                   	int3
  5432cd:	cc                   	int3
  5432ce:	cc                   	int3
  5432cf:	cc                   	int3
  5432d0:	56                   	push   esi
  5432d1:	8b f1                	mov    esi,ecx
  5432d3:	e8 88 8e f4 ff       	call   0x48c160
  5432d8:	85 c0                	test   eax,eax
  5432da:	74 04                	je     0x5432e0
  5432dc:	33 c0                	xor    eax,eax
  5432de:	5e                   	pop    esi
  5432df:	c3                   	ret
  5432e0:	69 ce 68 05 00 00    	imul   ecx,esi,0x568
  5432e6:	8b 81 e4 15 15 06    	mov    eax,DWORD PTR [ecx+0x61515e4]
  5432ec:	a9 00 02 00 00       	test   eax,0x200
  5432f1:	75 05                	jne    0x5432f8
  5432f3:	05 00 02 00 00       	add    eax,0x200
  5432f8:	89 81 e4 15 15 06    	mov    DWORD PTR [ecx+0x61515e4],eax
  5432fe:	a1 e0 b8 72 0a       	mov    eax,ds:0xa72b8e0
  543303:	83 c0 3c             	add    eax,0x3c
  543306:	89 81 20 19 15 06    	mov    DWORD PTR [ecx+0x6151920],eax
  54330c:	83 fe ff             	cmp    esi,0xffffffff
  54330f:	74 24                	je     0x543335
  543311:	80 b9 00 14 15 06 01 	cmp    BYTE PTR [ecx+0x6151400],0x1
  543318:	74 1b                	je     0x543335
  54331a:	83 ca ff             	or     edx,0xffffffff
  54331d:	8b ce                	mov    ecx,esi
  54331f:	e8 8c ce ed ff       	call   0x4201b0
  543324:	6a 3c                	push   0x3c
  543326:	ba 02 00 00 00       	mov    edx,0x2
  54332b:	8b ce                	mov    ecx,esi
  54332d:	e8 ee 13 ee ff       	call   0x424720
  543332:	83 c4 04             	add    esp,0x4
  543335:	b8 01 00 00 00       	mov    eax,0x1
  54333a:	5e                   	pop    esi
  54333b:	c3                   	ret
  54333c:	cc                   	int3
  54333d:	cc                   	int3
  54333e:	cc                   	int3
  54333f:	cc                   	int3
  543340:	55                   	push   ebp
  543341:	8b ec                	mov    ebp,esp
  543343:	81 ec c4 05 00 00    	sub    esp,0x5c4
  543349:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  54334e:	33 c5                	xor    eax,ebp
  543350:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  543353:	80 3d eb e0 b8 04 00 	cmp    BYTE PTR ds:0x4b8e0eb,0x0
  54335a:	53                   	push   ebx
  54335b:	56                   	push   esi
  54335c:	8b d9                	mov    ebx,ecx
  54335e:	89 95 44 fa ff ff    	mov    DWORD PTR [ebp-0x5bc],edx
  543364:	57                   	push   edi
  543365:	89 9d 48 fa ff ff    	mov    DWORD PTR [ebp-0x5b8],ebx
  54336b:	c7 85 4c fa ff ff 00 	mov    DWORD PTR [ebp-0x5b4],0x0
  543372:	00 00 00 
  543375:	c6 85 67 fa ff ff 00 	mov    BYTE PTR [ebp-0x599],0x0
  54337c:	74 0c                	je     0x54338a
  54337e:	c7 85 40 fa ff ff 32 	mov    DWORD PTR [ebp-0x5c0],0x32
  543385:	00 00 00 
  543388:	eb 46                	jmp    0x5433d0
  54338a:	e8 e1 5c ed ff       	call   0x419070
  54338f:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  543395:	2b c8                	sub    ecx,eax
  543397:	8b c1                	mov    eax,ecx
  543399:	8b cb                	mov    ecx,ebx
  54339b:	99                   	cdq
  54339c:	8b f0                	mov    esi,eax
  54339e:	33 f2                	xor    esi,edx
  5433a0:	2b f2                	sub    esi,edx
  5433a2:	e8 19 5d ed ff       	call   0x4190c0
  5433a7:	8b 0d 40 bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd40
  5433ad:	2b c8                	sub    ecx,eax
  5433af:	c7 85 54 fa ff ff 01 	mov    DWORD PTR [ebp-0x5ac],0x1
  5433b6:	00 00 00 
  5433b9:	8b c1                	mov    eax,ecx
  5433bb:	99                   	cdq
  5433bc:	33 c2                	xor    eax,edx
  5433be:	2b c2                	sub    eax,edx
  5433c0:	3b f0                	cmp    esi,eax
  5433c2:	0f 4f c6             	cmovg  eax,esi
  5433c5:	89 85 40 fa ff ff    	mov    DWORD PTR [ebp-0x5c0],eax
  5433cb:	83 f8 0a             	cmp    eax,0xa
  5433ce:	7e 0a                	jle    0x5433da
  5433d0:	c7 85 54 fa ff ff 00 	mov    DWORD PTR [ebp-0x5ac],0x0
  5433d7:	00 00 00 
  5433da:	33 c0                	xor    eax,eax
  5433dc:	8d bd 68 fa ff ff    	lea    edi,[ebp-0x598]
  5433e2:	b9 64 00 00 00       	mov    ecx,0x64
  5433e7:	f3 ab                	rep stos DWORD PTR es:[edi],eax
  5433e9:	69 cb 68 05 00 00    	imul   ecx,ebx,0x568
  5433ef:	bb b4 28 6d 0a       	mov    ebx,0xa6d28b4
  5433f4:	89 8d 50 fa ff ff    	mov    DWORD PTR [ebp-0x5b0],ecx
  5433fa:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  543400:	80 7b f8 04          	cmp    BYTE PTR [ebx-0x8],0x4
  543404:	0f 85 91 00 00 00    	jne    0x54349b
  54340a:	8b 3b                	mov    edi,DWORD PTR [ebx]
  54340c:	81 ff e8 03 00 00    	cmp    edi,0x3e8
  543412:	7c 06                	jl     0x54341a
  543414:	81 c7 18 fc ff ff    	add    edi,0xfffffc18
  54341a:	85 ff                	test   edi,edi
  54341c:	78 7d                	js     0x54349b
  54341e:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  543424:	80 b8 00 14 15 06 01 	cmp    BYTE PTR [eax+0x6151400],0x1
  54342b:	74 6e                	je     0x54349b
  54342d:	83 ff ff             	cmp    edi,0xffffffff
  543430:	74 09                	je     0x54343b
  543432:	80 b8 01 14 15 06 09 	cmp    BYTE PTR [eax+0x6151401],0x9
  543439:	74 09                	je     0x543444
  54343b:	83 b8 60 14 15 06 ff 	cmp    DWORD PTR [eax+0x6151460],0xffffffff
  543442:	75 57                	jne    0x54349b
  543444:	8b 80 bc 14 15 06    	mov    eax,DWORD PTR [eax+0x61514bc]
  54344a:	3b 81 bc 14 15 06    	cmp    eax,DWORD PTR [ecx+0x61514bc]
  543450:	75 49                	jne    0x54349b
  543452:	80 3d eb e0 b8 04 00 	cmp    BYTE PTR ds:0x4b8e0eb,0x0
  543459:	75 2c                	jne    0x543487
  54345b:	0f b7 4b f4          	movzx  ecx,WORD PTR [ebx-0xc]
  54345f:	a1 9c 1c 6d 0a       	mov    eax,ds:0xa6d1c9c
  543464:	2b c1                	sub    eax,ecx
  543466:	0f b7 4b f6          	movzx  ecx,WORD PTR [ebx-0xa]
  54346a:	99                   	cdq
  54346b:	8b f0                	mov    esi,eax
  54346d:	a1 40 bd 72 0a       	mov    eax,ds:0xa72bd40
  543472:	33 f2                	xor    esi,edx
  543474:	2b c1                	sub    eax,ecx
  543476:	2b f2                	sub    esi,edx
  543478:	99                   	cdq
  543479:	33 c2                	xor    eax,edx
  54347b:	2b c2                	sub    eax,edx
  54347d:	3b f0                	cmp    esi,eax
  54347f:	0f 4f c6             	cmovg  eax,esi
  543482:	83 f8 32             	cmp    eax,0x32
  543485:	7f 14                	jg     0x54349b
  543487:	8b 85 4c fa ff ff    	mov    eax,DWORD PTR [ebp-0x5b4]
  54348d:	89 bc 85 68 fa ff ff 	mov    DWORD PTR [ebp+eax*4-0x598],edi
  543494:	40                   	inc    eax
  543495:	89 85 4c fa ff ff    	mov    DWORD PTR [ebp-0x5b4],eax
  54349b:	8b 8d 50 fa ff ff    	mov    ecx,DWORD PTR [ebp-0x5b0]
  5434a1:	83 c3 24             	add    ebx,0x24
  5434a4:	81 fb f4 a6 72 0a    	cmp    ebx,0xa72a6f4
  5434aa:	0f 8c 50 ff ff ff    	jl     0x543400
  5434b0:	33 f6                	xor    esi,esi
  5434b2:	33 db                	xor    ebx,ebx
  5434b4:	89 b5 5c fa ff ff    	mov    DWORD PTR [ebp-0x5a4],esi
  5434ba:	89 9d 58 fa ff ff    	mov    DWORD PTR [ebp-0x5a8],ebx
  5434c0:	e8 db c5 fb ff       	call   0x4ffaa0
  5434c5:	8b bd 50 fa ff ff    	mov    edi,DWORD PTR [ebp-0x5b0]
  5434cb:	39 9f 24 19 15 06    	cmp    DWORD PTR [edi+0x6151924],ebx
  5434d1:	75 0c                	jne    0x5434df
  5434d3:	39 9f 28 19 15 06    	cmp    DWORD PTR [edi+0x6151928],ebx
  5434d9:	0f 84 26 01 00 00    	je     0x543605
  5434df:	39 9d 44 fa ff ff    	cmp    DWORD PTR [ebp-0x5bc],ebx
  5434e5:	0f 85 1a 01 00 00    	jne    0x543605
  5434eb:	39 9d 54 fa ff ff    	cmp    DWORD PTR [ebp-0x5ac],ebx
  5434f1:	0f 84 03 01 00 00    	je     0x5435fa
  5434f7:	a1 e4 62 5b 00       	mov    eax,ds:0x5b62e4
  5434fc:	89 85 f8 fb ff ff    	mov    DWORD PTR [ebp-0x408],eax
  543502:	a1 e8 62 5b 00       	mov    eax,ds:0x5b62e8
  543507:	89 85 fc fb ff ff    	mov    DWORD PTR [ebp-0x404],eax
  54350d:	38 9d 67 fa ff ff    	cmp    BYTE PTR [ebp-0x599],bl
  543513:	74 2e                	je     0x543543
  543515:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  54351b:	49                   	dec    ecx
  54351c:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  543520:	8a 41 01             	mov    al,BYTE PTR [ecx+0x1]
  543523:	8d 49 01             	lea    ecx,[ecx+0x1]
  543526:	84 c0                	test   al,al
  543528:	75 f6                	jne    0x543520
  54352a:	a1 ec 62 5b 00       	mov    eax,ds:0x5b62ec
  54352f:	89 01                	mov    DWORD PTR [ecx],eax
  543531:	66 a1 f0 62 5b 00    	mov    ax,ds:0x5b62f0
  543537:	66 89 41 04          	mov    WORD PTR [ecx+0x4],ax
  54353b:	a0 f2 62 5b 00       	mov    al,ds:0x5b62f2
  543540:	88 41 06             	mov    BYTE PTR [ecx+0x6],al
  543543:	8b 15 98 96 5a 06    	mov    edx,DWORD PTR ds:0x65a9698
  543549:	33 ff                	xor    edi,edi
  54354b:	83 fa 32             	cmp    edx,0x32
  54354e:	0f 8f 93 00 00 00    	jg     0x5435e7
  543554:	b9 88 f9 59 06       	mov    ecx,0x659f988
  543559:	8d 51 01             	lea    edx,[ecx+0x1]
  54355c:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  543560:	8a 01                	mov    al,BYTE PTR [ecx]
  543562:	41                   	inc    ecx
  543563:	84 c0                	test   al,al
  543565:	75 f9                	jne    0x543560
  543567:	2b ca                	sub    ecx,edx
  543569:	74 20                	je     0x54358b
  54356b:	ba 88 f9 59 06       	mov    edx,0x659f988
  543570:	47                   	inc    edi
  543571:	81 c2 0c 02 00 00    	add    edx,0x20c
  543577:	8b ca                	mov    ecx,edx
  543579:	8d 71 01             	lea    esi,[ecx+0x1]
  54357c:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  543580:	8a 01                	mov    al,BYTE PTR [ecx]
  543582:	41                   	inc    ecx
  543583:	84 c0                	test   al,al
  543585:	75 f9                	jne    0x543580
  543587:	2b ce                	sub    ecx,esi
  543589:	75 e5                	jne    0x543570
  54358b:	69 df 0c 02 00 00    	imul   ebx,edi,0x20c
  543591:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  543597:	50                   	push   eax
  543598:	6a 45                	push   0x45
  54359a:	68 08 5a 59 00       	push   0x595a08
  54359f:	8d b3 88 f9 59 06    	lea    esi,[ebx+0x659f988]
  5435a5:	56                   	push   esi
  5435a6:	e8 25 db eb ff       	call   0x4010d0
  5435ab:	83 c4 10             	add    esp,0x10
  5435ae:	8d 4e 01             	lea    ecx,[esi+0x1]
  5435b1:	8a 06                	mov    al,BYTE PTR [esi]
  5435b3:	46                   	inc    esi
  5435b4:	84 c0                	test   al,al
  5435b6:	75 f9                	jne    0x5435b1
  5435b8:	2b f1                	sub    esi,ecx
  5435ba:	83 fe 22             	cmp    esi,0x22
  5435bd:	76 0f                	jbe    0x5435ce
  5435bf:	66 c7 83 a8 f9 59 06 	mov    WORD PTR [ebx+0x659f9a8],0x2e2e
  5435c6:	2e 2e 
  5435c8:	88 83 aa f9 59 06    	mov    BYTE PTR [ebx+0x659f9aa],al
  5435ce:	8d 57 01             	lea    edx,[edi+0x1]
  5435d1:	c7 83 50 fa 59 06 45 	mov    DWORD PTR [ebx+0x659fa50],0x45
  5435d8:	00 00 00 
  5435db:	8b 9d 58 fa ff ff    	mov    ebx,DWORD PTR [ebp-0x5a8]
  5435e1:	89 15 98 96 5a 06    	mov    DWORD PTR ds:0x65a9698,edx
  5435e7:	8b bd 50 fa ff ff    	mov    edi,DWORD PTR [ebp-0x5b0]
  5435ed:	be 01 00 00 00       	mov    esi,0x1
  5435f2:	89 b5 5c fa ff ff    	mov    DWORD PTR [ebp-0x5a4],esi
  5435f8:	eb 11                	jmp    0x54360b
  5435fa:	bb 01 00 00 00       	mov    ebx,0x1
  5435ff:	89 9d 58 fa ff ff    	mov    DWORD PTR [ebp-0x5a8],ebx
  543605:	8b 15 98 96 5a 06    	mov    edx,DWORD PTR ds:0x65a9698
  54360b:	81 bf bc 14 15 06 6a 	cmp    DWORD PTR [edi+0x61514bc],0x26a
  543612:	02 00 00 
  543615:	0f 85 01 01 00 00    	jne    0x54371c
  54361b:	80 bd 67 fa ff ff 00 	cmp    BYTE PTR [ebp-0x599],0x0
  543622:	a1 f4 62 5b 00       	mov    eax,ds:0x5b62f4
  543627:	89 85 f8 fb ff ff    	mov    DWORD PTR [ebp-0x408],eax
  54362d:	66 a1 f8 62 5b 00    	mov    ax,ds:0x5b62f8
  543633:	66 89 85 fc fb ff ff 	mov    WORD PTR [ebp-0x404],ax
  54363a:	a0 fa 62 5b 00       	mov    al,ds:0x5b62fa
  54363f:	88 85 fe fb ff ff    	mov    BYTE PTR [ebp-0x402],al
  543645:	74 2c                	je     0x543673
  543647:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  54364d:	49                   	dec    ecx
  54364e:	66 90                	xchg   ax,ax
  543650:	8a 41 01             	mov    al,BYTE PTR [ecx+0x1]
  543653:	8d 49 01             	lea    ecx,[ecx+0x1]
  543656:	84 c0                	test   al,al
  543658:	75 f6                	jne    0x543650
  54365a:	a1 ec 62 5b 00       	mov    eax,ds:0x5b62ec
  54365f:	89 01                	mov    DWORD PTR [ecx],eax
  543661:	66 a1 f0 62 5b 00    	mov    ax,ds:0x5b62f0
  543667:	66 89 41 04          	mov    WORD PTR [ecx+0x4],ax
  54366b:	a0 f2 62 5b 00       	mov    al,ds:0x5b62f2
  543670:	88 41 06             	mov    BYTE PTR [ecx+0x6],al
  543673:	33 db                	xor    ebx,ebx
  543675:	83 fa 32             	cmp    edx,0x32
  543678:	0f 8f 91 00 00 00    	jg     0x54370f
  54367e:	b9 88 f9 59 06       	mov    ecx,0x659f988
  543683:	8d 51 01             	lea    edx,[ecx+0x1]
  543686:	8a 01                	mov    al,BYTE PTR [ecx]
  543688:	41                   	inc    ecx
  543689:	84 c0                	test   al,al
  54368b:	75 f9                	jne    0x543686
  54368d:	2b ca                	sub    ecx,edx
  54368f:	74 1c                	je     0x5436ad
  543691:	ba 88 f9 59 06       	mov    edx,0x659f988
  543696:	43                   	inc    ebx
  543697:	81 c2 0c 02 00 00    	add    edx,0x20c
  54369d:	8b ca                	mov    ecx,edx
  54369f:	8d 71 01             	lea    esi,[ecx+0x1]
  5436a2:	8a 01                	mov    al,BYTE PTR [ecx]
  5436a4:	41                   	inc    ecx
  5436a5:	84 c0                	test   al,al
  5436a7:	75 f9                	jne    0x5436a2
  5436a9:	2b ce                	sub    ecx,esi
  5436ab:	75 e9                	jne    0x543696
  5436ad:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  5436b3:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  5436b9:	50                   	push   eax
  5436ba:	6a 41                	push   0x41
  5436bc:	68 08 5a 59 00       	push   0x595a08
  5436c1:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  5436c7:	56                   	push   esi
  5436c8:	e8 03 da eb ff       	call   0x4010d0
  5436cd:	83 c4 10             	add    esp,0x10
  5436d0:	8d 4e 01             	lea    ecx,[esi+0x1]
  5436d3:	8a 06                	mov    al,BYTE PTR [esi]
  5436d5:	46                   	inc    esi
  5436d6:	84 c0                	test   al,al
  5436d8:	75 f9                	jne    0x5436d3
  5436da:	2b f1                	sub    esi,ecx
  5436dc:	83 fe 22             	cmp    esi,0x22
  5436df:	76 0f                	jbe    0x5436f0
  5436e1:	66 c7 87 a8 f9 59 06 	mov    WORD PTR [edi+0x659f9a8],0x2e2e
  5436e8:	2e 2e 
  5436ea:	88 87 aa f9 59 06    	mov    BYTE PTR [edi+0x659f9aa],al
  5436f0:	8b b5 5c fa ff ff    	mov    esi,DWORD PTR [ebp-0x5a4]
  5436f6:	8d 53 01             	lea    edx,[ebx+0x1]
  5436f9:	c7 87 50 fa 59 06 41 	mov    DWORD PTR [edi+0x659fa50],0x41
  543700:	00 00 00 
  543703:	8b bd 50 fa ff ff    	mov    edi,DWORD PTR [ebp-0x5b0]
  543709:	89 15 98 96 5a 06    	mov    DWORD PTR ds:0x65a9698,edx
  54370f:	8b 9d 58 fa ff ff    	mov    ebx,DWORD PTR [ebp-0x5a8]
  543715:	46                   	inc    esi
  543716:	89 b5 5c fa ff ff    	mov    DWORD PTR [ebp-0x5a4],esi
  54371c:	8b 8d 48 fa ff ff    	mov    ecx,DWORD PTR [ebp-0x5b8]
  543722:	e8 69 60 f6 ff       	call   0x4a9790
  543727:	85 c0                	test   eax,eax
  543729:	0f 85 2f 02 00 00    	jne    0x54395e
  54372f:	38 85 67 fa ff ff    	cmp    BYTE PTR [ebp-0x599],al
  543735:	0f 85 23 02 00 00    	jne    0x54395e
  54373b:	f6 87 dd 15 15 06 01 	test   BYTE PTR [edi+0x61515dd],0x1
  543742:	0f 84 16 02 00 00    	je     0x54395e
  543748:	f7 87 e4 15 15 06 00 	test   DWORD PTR [edi+0x61515e4],0x200
  54374f:	02 00 00 
  543752:	0f 84 94 00 00 00    	je     0x5437ec
  543758:	33 db                	xor    ebx,ebx
  54375a:	83 fa 32             	cmp    edx,0x32
  54375d:	0f 8f f4 01 00 00    	jg     0x543957
  543763:	b9 88 f9 59 06       	mov    ecx,0x659f988
  543768:	8d 51 01             	lea    edx,[ecx+0x1]
  54376b:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  543770:	8a 01                	mov    al,BYTE PTR [ecx]
  543772:	41                   	inc    ecx
  543773:	84 c0                	test   al,al
  543775:	75 f9                	jne    0x543770
  543777:	2b ca                	sub    ecx,edx
  543779:	74 20                	je     0x54379b
  54377b:	ba 88 f9 59 06       	mov    edx,0x659f988
  543780:	43                   	inc    ebx
  543781:	81 c2 0c 02 00 00    	add    edx,0x20c
  543787:	8b ca                	mov    ecx,edx
  543789:	8d 71 01             	lea    esi,[ecx+0x1]
  54378c:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  543790:	8a 01                	mov    al,BYTE PTR [ecx]
  543792:	41                   	inc    ecx
  543793:	84 c0                	test   al,al
  543795:	75 f9                	jne    0x543790
  543797:	2b ce                	sub    ecx,esi
  543799:	75 e5                	jne    0x543780
  54379b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  5437a1:	68 fc 62 5b 00       	push   0x5b62fc
  5437a6:	6a 46                	push   0x46
  5437a8:	68 08 5a 59 00       	push   0x595a08
  5437ad:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  5437b3:	56                   	push   esi
  5437b4:	e8 17 d9 eb ff       	call   0x4010d0
  5437b9:	83 c4 10             	add    esp,0x10
  5437bc:	8d 4e 01             	lea    ecx,[esi+0x1]
  5437bf:	90                   	nop
  5437c0:	8a 06                	mov    al,BYTE PTR [esi]
  5437c2:	46                   	inc    esi
  5437c3:	84 c0                	test   al,al
  5437c5:	75 f9                	jne    0x5437c0
  5437c7:	2b f1                	sub    esi,ecx
  5437c9:	83 fe 22             	cmp    esi,0x22
  5437cc:	76 0f                	jbe    0x5437dd
  5437ce:	66 c7 87 a8 f9 59 06 	mov    WORD PTR [edi+0x659f9a8],0x2e2e
  5437d5:	2e 2e 
  5437d7:	88 87 aa f9 59 06    	mov    BYTE PTR [edi+0x659f9aa],al
  5437dd:	c7 87 50 fa 59 06 46 	mov    DWORD PTR [edi+0x659fa50],0x46
  5437e4:	00 00 00 
  5437e7:	e9 5c 01 00 00       	jmp    0x543948
  5437ec:	83 bd 44 fa ff ff 00 	cmp    DWORD PTR [ebp-0x5bc],0x0
  5437f3:	0f 85 bd 00 00 00    	jne    0x5438b6
  5437f9:	83 bd 54 fa ff ff 00 	cmp    DWORD PTR [ebp-0x5ac],0x0
  543800:	0f 84 a9 00 00 00    	je     0x5438af
  543806:	33 db                	xor    ebx,ebx
  543808:	83 fa 32             	cmp    edx,0x32
  54380b:	0f 8f 95 00 00 00    	jg     0x5438a6
  543811:	b9 88 f9 59 06       	mov    ecx,0x659f988
  543816:	8d 51 01             	lea    edx,[ecx+0x1]
  543819:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  543820:	8a 01                	mov    al,BYTE PTR [ecx]
  543822:	41                   	inc    ecx
  543823:	84 c0                	test   al,al
  543825:	75 f9                	jne    0x543820
  543827:	2b ca                	sub    ecx,edx
  543829:	74 20                	je     0x54384b
  54382b:	ba 88 f9 59 06       	mov    edx,0x659f988
  543830:	43                   	inc    ebx
  543831:	81 c2 0c 02 00 00    	add    edx,0x20c
  543837:	8b ca                	mov    ecx,edx
  543839:	8d 71 01             	lea    esi,[ecx+0x1]
  54383c:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  543840:	8a 01                	mov    al,BYTE PTR [ecx]
  543842:	41                   	inc    ecx
  543843:	84 c0                	test   al,al
  543845:	75 f9                	jne    0x543840
  543847:	2b ce                	sub    ecx,esi
  543849:	75 e5                	jne    0x543830
  54384b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  543851:	68 04 63 5b 00       	push   0x5b6304
  543856:	6a 53                	push   0x53
  543858:	68 08 5a 59 00       	push   0x595a08
  54385d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  543863:	56                   	push   esi
  543864:	e8 67 d8 eb ff       	call   0x4010d0
  543869:	83 c4 10             	add    esp,0x10
  54386c:	8d 4e 01             	lea    ecx,[esi+0x1]
  54386f:	90                   	nop
  543870:	8a 06                	mov    al,BYTE PTR [esi]
  543872:	46                   	inc    esi
  543873:	84 c0                	test   al,al
  543875:	75 f9                	jne    0x543870
  543877:	2b f1                	sub    esi,ecx
  543879:	83 fe 22             	cmp    esi,0x22
  54387c:	76 0f                	jbe    0x54388d
  54387e:	66 c7 87 a8 f9 59 06 	mov    WORD PTR [edi+0x659f9a8],0x2e2e
  543885:	2e 2e 
  543887:	88 87 aa f9 59 06    	mov    BYTE PTR [edi+0x659f9aa],al
  54388d:	8b b5 5c fa ff ff    	mov    esi,DWORD PTR [ebp-0x5a4]
  543893:	8d 53 01             	lea    edx,[ebx+0x1]
  543896:	c7 87 50 fa 59 06 53 	mov    DWORD PTR [edi+0x659fa50],0x53
  54389d:	00 00 00 
  5438a0:	89 15 98 96 5a 06    	mov    DWORD PTR ds:0x65a9698,edx
  5438a6:	46                   	inc    esi
  5438a7:	89 b5 5c fa ff ff    	mov    DWORD PTR [ebp-0x5a4],esi
  5438ad:	eb 07                	jmp    0x5438b6
  5438af:	43                   	inc    ebx
  5438b0:	89 9d 58 fa ff ff    	mov    DWORD PTR [ebp-0x5a8],ebx
  5438b6:	83 bd 40 fa ff ff 02 	cmp    DWORD PTR [ebp-0x5c0],0x2
  5438bd:	0f 8e 9b 00 00 00    	jle    0x54395e
  5438c3:	33 db                	xor    ebx,ebx
  5438c5:	83 fa 32             	cmp    edx,0x32
  5438c8:	0f 8f 89 00 00 00    	jg     0x543957
  5438ce:	b9 88 f9 59 06       	mov    ecx,0x659f988
  5438d3:	8d 51 01             	lea    edx,[ecx+0x1]
  5438d6:	8a 01                	mov    al,BYTE PTR [ecx]
  5438d8:	41                   	inc    ecx
  5438d9:	84 c0                	test   al,al
  5438db:	75 f9                	jne    0x5438d6
  5438dd:	2b ca                	sub    ecx,edx
  5438df:	74 1c                	je     0x5438fd
  5438e1:	ba 88 f9 59 06       	mov    edx,0x659f988
  5438e6:	43                   	inc    ebx
  5438e7:	81 c2 0c 02 00 00    	add    edx,0x20c
  5438ed:	8b ca                	mov    ecx,edx
  5438ef:	8d 71 01             	lea    esi,[ecx+0x1]
  5438f2:	8a 01                	mov    al,BYTE PTR [ecx]
  5438f4:	41                   	inc    ecx
  5438f5:	84 c0                	test   al,al
  5438f7:	75 f9                	jne    0x5438f2
  5438f9:	2b ce                	sub    ecx,esi
  5438fb:	75 e9                	jne    0x5438e6
  5438fd:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  543903:	68 0c 63 5b 00       	push   0x5b630c
  543908:	6a 43                	push   0x43
  54390a:	68 08 5a 59 00       	push   0x595a08
  54390f:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  543915:	56                   	push   esi
  543916:	e8 b5 d7 eb ff       	call   0x4010d0
  54391b:	83 c4 10             	add    esp,0x10
  54391e:	8d 4e 01             	lea    ecx,[esi+0x1]
  543921:	8a 06                	mov    al,BYTE PTR [esi]
  543923:	46                   	inc    esi
  543924:	84 c0                	test   al,al
  543926:	75 f9                	jne    0x543921
  543928:	2b f1                	sub    esi,ecx
  54392a:	83 fe 22             	cmp    esi,0x22
  54392d:	76 0f                	jbe    0x54393e
  54392f:	66 c7 87 a8 f9 59 06 	mov    WORD PTR [edi+0x659f9a8],0x2e2e
  543936:	2e 2e 
  543938:	88 87 aa f9 59 06    	mov    BYTE PTR [edi+0x659f9aa],al
  54393e:	c7 87 50 fa 59 06 43 	mov    DWORD PTR [edi+0x659fa50],0x43
  543945:	00 00 00 
  543948:	8b b5 5c fa ff ff    	mov    esi,DWORD PTR [ebp-0x5a4]
  54394e:	8d 53 01             	lea    edx,[ebx+0x1]
  543951:	89 15 98 96 5a 06    	mov    DWORD PTR ds:0x65a9698,edx
  543957:	46                   	inc    esi
  543958:	89 b5 5c fa ff ff    	mov    DWORD PTR [ebp-0x5a4],esi
  54395e:	8b 8d 44 fa ff ff    	mov    ecx,DWORD PTR [ebp-0x5bc]
  543964:	8b 9d 54 fa ff ff    	mov    ebx,DWORD PTR [ebp-0x5ac]
  54396a:	85 c9                	test   ecx,ecx
  54396c:	0f 85 c1 00 00 00    	jne    0x543a33
  543972:	38 8d 67 fa ff ff    	cmp    BYTE PTR [ebp-0x599],cl
  543978:	0f 85 b5 00 00 00    	jne    0x543a33
  54397e:	85 db                	test   ebx,ebx
  543980:	0f 84 1e 02 00 00    	je     0x543ba4
  543986:	33 db                	xor    ebx,ebx
  543988:	83 fa 32             	cmp    edx,0x32
  54398b:	0f 8f 9b 00 00 00    	jg     0x543a2c
  543991:	b9 88 f9 59 06       	mov    ecx,0x659f988
  543996:	8d 51 01             	lea    edx,[ecx+0x1]
  543999:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  5439a0:	8a 01                	mov    al,BYTE PTR [ecx]
  5439a2:	41                   	inc    ecx
  5439a3:	84 c0                	test   al,al
  5439a5:	75 f9                	jne    0x5439a0
  5439a7:	2b ca                	sub    ecx,edx
  5439a9:	74 20                	je     0x5439cb
  5439ab:	ba 88 f9 59 06       	mov    edx,0x659f988
  5439b0:	43                   	inc    ebx
  5439b1:	81 c2 0c 02 00 00    	add    edx,0x20c
  5439b7:	8b ca                	mov    ecx,edx
  5439b9:	8d 71 01             	lea    esi,[ecx+0x1]
  5439bc:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  5439c0:	8a 01                	mov    al,BYTE PTR [ecx]
  5439c2:	41                   	inc    ecx
  5439c3:	84 c0                	test   al,al
  5439c5:	75 f9                	jne    0x5439c0
  5439c7:	2b ce                	sub    ecx,esi
  5439c9:	75 e5                	jne    0x5439b0
  5439cb:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  5439d1:	68 14 63 5b 00       	push   0x5b6314
  5439d6:	6a 4e                	push   0x4e
  5439d8:	68 08 5a 59 00       	push   0x595a08
  5439dd:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  5439e3:	56                   	push   esi
  5439e4:	e8 e7 d6 eb ff       	call   0x4010d0
  5439e9:	83 c4 10             	add    esp,0x10
  5439ec:	8d 4e 01             	lea    ecx,[esi+0x1]
  5439ef:	90                   	nop
  5439f0:	8a 06                	mov    al,BYTE PTR [esi]
  5439f2:	46                   	inc    esi
  5439f3:	84 c0                	test   al,al
  5439f5:	75 f9                	jne    0x5439f0
  5439f7:	2b f1                	sub    esi,ecx
  5439f9:	83 fe 22             	cmp    esi,0x22
  5439fc:	76 0f                	jbe    0x543a0d
  5439fe:	66 c7 87 a8 f9 59 06 	mov    WORD PTR [edi+0x659f9a8],0x2e2e
  543a05:	2e 2e 
  543a07:	88 87 aa f9 59 06    	mov    BYTE PTR [edi+0x659f9aa],al
  543a0d:	8b b5 5c fa ff ff    	mov    esi,DWORD PTR [ebp-0x5a4]
  543a13:	8d 53 01             	lea    edx,[ebx+0x1]
  543a16:	8b 8d 44 fa ff ff    	mov    ecx,DWORD PTR [ebp-0x5bc]
  543a1c:	c7 87 50 fa 59 06 4e 	mov    DWORD PTR [edi+0x659fa50],0x4e
  543a23:	00 00 00 
  543a26:	89 15 98 96 5a 06    	mov    DWORD PTR ds:0x65a9698,edx
  543a2c:	8b 9d 54 fa ff ff    	mov    ebx,DWORD PTR [ebp-0x5ac]
  543a32:	46                   	inc    esi
  543a33:	8b 85 58 fa ff ff    	mov    eax,DWORD PTR [ebp-0x5a8]
  543a39:	85 f6                	test   esi,esi
  543a3b:	0f 84 b1 05 00 00    	je     0x543ff2
  543a41:	85 c9                	test   ecx,ecx
  543a43:	75 14                	jne    0x543a59
  543a45:	85 c0                	test   eax,eax
  543a47:	7e 10                	jle    0x543a59
  543a49:	b9 d0 63 5b 00       	mov    ecx,0x5b63d0
  543a4e:	e8 bd 2a fb ff       	call   0x4f6510
  543a53:	8b 15 98 96 5a 06    	mov    edx,DWORD PTR ds:0x65a9698
  543a59:	83 bd 4c fa ff ff 01 	cmp    DWORD PTR [ebp-0x5b4],0x1
  543a60:	0f 8e d9 01 00 00    	jle    0x543c3f
  543a66:	33 ff                	xor    edi,edi
  543a68:	83 fa 32             	cmp    edx,0x32
  543a6b:	0f 8f 8f 00 00 00    	jg     0x543b00
  543a71:	b9 88 f9 59 06       	mov    ecx,0x659f988
  543a76:	8d 51 01             	lea    edx,[ecx+0x1]
  543a79:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  543a80:	8a 01                	mov    al,BYTE PTR [ecx]
  543a82:	41                   	inc    ecx
  543a83:	84 c0                	test   al,al
  543a85:	75 f9                	jne    0x543a80
  543a87:	2b ca                	sub    ecx,edx
  543a89:	74 20                	je     0x543aab
  543a8b:	ba 88 f9 59 06       	mov    edx,0x659f988
  543a90:	47                   	inc    edi
  543a91:	81 c2 0c 02 00 00    	add    edx,0x20c
  543a97:	8b ca                	mov    ecx,edx
  543a99:	8d 71 01             	lea    esi,[ecx+0x1]
  543a9c:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  543aa0:	8a 01                	mov    al,BYTE PTR [ecx]
  543aa2:	41                   	inc    ecx
  543aa3:	84 c0                	test   al,al
  543aa5:	75 f9                	jne    0x543aa0
  543aa7:	2b ce                	sub    ecx,esi
  543aa9:	75 e5                	jne    0x543a90
  543aab:	69 df 0c 02 00 00    	imul   ebx,edi,0x20c
  543ab1:	68 16 c6 58 00       	push   0x58c616
  543ab6:	6a ff                	push   0xffffffff
  543ab8:	68 08 5a 59 00       	push   0x595a08
  543abd:	8d b3 88 f9 59 06    	lea    esi,[ebx+0x659f988]
  543ac3:	56                   	push   esi
  543ac4:	e8 07 d6 eb ff       	call   0x4010d0
  543ac9:	83 c4 10             	add    esp,0x10
  543acc:	8d 4e 01             	lea    ecx,[esi+0x1]
  543acf:	90                   	nop
  543ad0:	8a 06                	mov    al,BYTE PTR [esi]
  543ad2:	46                   	inc    esi
  543ad3:	84 c0                	test   al,al
  543ad5:	75 f9                	jne    0x543ad0
  543ad7:	2b f1                	sub    esi,ecx
  543ad9:	83 fe 22             	cmp    esi,0x22
  543adc:	76 0f                	jbe    0x543aed
  543ade:	66 c7 83 a8 f9 59 06 	mov    WORD PTR [ebx+0x659f9a8],0x2e2e
  543ae5:	2e 2e 
  543ae7:	88 83 aa f9 59 06    	mov    BYTE PTR [ebx+0x659f9aa],al
  543aed:	8d 57 01             	lea    edx,[edi+0x1]
  543af0:	c7 83 50 fa 59 06 ff 	mov    DWORD PTR [ebx+0x659fa50],0xffffffff
  543af7:	ff ff ff 
  543afa:	89 15 98 96 5a 06    	mov    DWORD PTR ds:0x65a9698,edx
  543b00:	33 ff                	xor    edi,edi
  543b02:	80 bd 67 fa ff ff 00 	cmp    BYTE PTR [ebp-0x599],0x0
  543b09:	0f 85 a1 00 00 00    	jne    0x543bb0
  543b0f:	83 fa 32             	cmp    edx,0x32
  543b12:	0f 8f 30 01 00 00    	jg     0x543c48
  543b18:	b9 88 f9 59 06       	mov    ecx,0x659f988
  543b1d:	8d 51 01             	lea    edx,[ecx+0x1]
  543b20:	8a 01                	mov    al,BYTE PTR [ecx]
  543b22:	41                   	inc    ecx
  543b23:	84 c0                	test   al,al
  543b25:	75 f9                	jne    0x543b20
  543b27:	2b ca                	sub    ecx,edx
  543b29:	74 20                	je     0x543b4b
  543b2b:	ba 88 f9 59 06       	mov    edx,0x659f988
  543b30:	47                   	inc    edi
  543b31:	81 c2 0c 02 00 00    	add    edx,0x20c
  543b37:	8b ca                	mov    ecx,edx
  543b39:	8d 71 01             	lea    esi,[ecx+0x1]
  543b3c:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  543b40:	8a 01                	mov    al,BYTE PTR [ecx]
  543b42:	41                   	inc    ecx
  543b43:	84 c0                	test   al,al
  543b45:	75 f9                	jne    0x543b40
  543b47:	2b ce                	sub    ecx,esi
  543b49:	75 e5                	jne    0x543b30
  543b4b:	69 df 0c 02 00 00    	imul   ebx,edi,0x20c
  543b51:	68 28 63 5b 00       	push   0x5b6328
  543b56:	6a 2b                	push   0x2b
  543b58:	68 08 5a 59 00       	push   0x595a08
  543b5d:	8d b3 88 f9 59 06    	lea    esi,[ebx+0x659f988]
  543b63:	56                   	push   esi
  543b64:	e8 67 d5 eb ff       	call   0x4010d0
  543b69:	83 c4 10             	add    esp,0x10
  543b6c:	8d 4e 01             	lea    ecx,[esi+0x1]
  543b6f:	90                   	nop
  543b70:	8a 06                	mov    al,BYTE PTR [esi]
  543b72:	46                   	inc    esi
  543b73:	84 c0                	test   al,al
  543b75:	75 f9                	jne    0x543b70
  543b77:	2b f1                	sub    esi,ecx
  543b79:	83 fe 22             	cmp    esi,0x22
  543b7c:	76 0f                	jbe    0x543b8d
  543b7e:	66 c7 83 a8 f9 59 06 	mov    WORD PTR [ebx+0x659f9a8],0x2e2e
  543b85:	2e 2e 
  543b87:	88 83 aa f9 59 06    	mov    BYTE PTR [ebx+0x659f9aa],al
  543b8d:	8d 47 01             	lea    eax,[edi+0x1]
  543b90:	c7 83 50 fa 59 06 2b 	mov    DWORD PTR [ebx+0x659fa50],0x2b
  543b97:	00 00 00 
  543b9a:	a3 98 96 5a 06       	mov    ds:0x65a9698,eax
  543b9f:	e9 a4 00 00 00       	jmp    0x543c48
  543ba4:	8b 85 58 fa ff ff    	mov    eax,DWORD PTR [ebp-0x5a8]
  543baa:	40                   	inc    eax
  543bab:	e9 89 fe ff ff       	jmp    0x543a39
  543bb0:	83 fa 32             	cmp    edx,0x32
  543bb3:	0f 8f 86 00 00 00    	jg     0x543c3f
  543bb9:	b9 88 f9 59 06       	mov    ecx,0x659f988
  543bbe:	8d 51 01             	lea    edx,[ecx+0x1]
  543bc1:	8a 01                	mov    al,BYTE PTR [ecx]
  543bc3:	41                   	inc    ecx
  543bc4:	84 c0                	test   al,al
  543bc6:	75 f9                	jne    0x543bc1
  543bc8:	2b ca                	sub    ecx,edx
  543bca:	74 1f                	je     0x543beb
  543bcc:	ba 88 f9 59 06       	mov    edx,0x659f988
  543bd1:	47                   	inc    edi
  543bd2:	81 c2 0c 02 00 00    	add    edx,0x20c
  543bd8:	8b c2                	mov    eax,edx
  543bda:	8d 70 01             	lea    esi,[eax+0x1]
  543bdd:	0f 1f 00             	nop    DWORD PTR [eax]
  543be0:	8a 08                	mov    cl,BYTE PTR [eax]
  543be2:	40                   	inc    eax
  543be3:	84 c9                	test   cl,cl
  543be5:	75 f9                	jne    0x543be0
  543be7:	2b c6                	sub    eax,esi
  543be9:	75 e6                	jne    0x543bd1
  543beb:	69 df 0c 02 00 00    	imul   ebx,edi,0x20c
  543bf1:	68 38 63 5b 00       	push   0x5b6338
  543bf6:	6a 2d                	push   0x2d
  543bf8:	68 08 5a 59 00       	push   0x595a08
  543bfd:	8d b3 88 f9 59 06    	lea    esi,[ebx+0x659f988]
  543c03:	56                   	push   esi
  543c04:	e8 c7 d4 eb ff       	call   0x4010d0
  543c09:	83 c4 10             	add    esp,0x10
  543c0c:	8d 4e 01             	lea    ecx,[esi+0x1]
  543c0f:	90                   	nop
  543c10:	8a 06                	mov    al,BYTE PTR [esi]
  543c12:	46                   	inc    esi
  543c13:	84 c0                	test   al,al
  543c15:	75 f9                	jne    0x543c10
  543c17:	2b f1                	sub    esi,ecx
  543c19:	83 fe 22             	cmp    esi,0x22
  543c1c:	76 0f                	jbe    0x543c2d
  543c1e:	66 c7 83 a8 f9 59 06 	mov    WORD PTR [ebx+0x659f9a8],0x2e2e
  543c25:	2e 2e 
  543c27:	88 83 aa f9 59 06    	mov    BYTE PTR [ebx+0x659f9aa],al
  543c2d:	8d 47 01             	lea    eax,[edi+0x1]
  543c30:	c7 83 50 fa 59 06 2d 	mov    DWORD PTR [ebx+0x659fa50],0x2d
  543c37:	00 00 00 
  543c3a:	a3 98 96 5a 06       	mov    ds:0x65a9698,eax
  543c3f:	80 bd 67 fa ff ff 00 	cmp    BYTE PTR [ebp-0x599],0x0
  543c46:	75 26                	jne    0x543c6e
  543c48:	8b b5 48 fa ff ff    	mov    esi,DWORD PTR [ebp-0x5b8]
  543c4e:	33 d2                	xor    edx,edx
  543c50:	8b ce                	mov    ecx,esi
  543c52:	e8 99 98 f6 ff       	call   0x4ad4f0
  543c57:	50                   	push   eax
  543c58:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  543c5e:	68 4c 63 5b 00       	push   0x5b634c
  543c63:	50                   	push   eax
  543c64:	e8 67 d4 eb ff       	call   0x4010d0
  543c69:	83 c4 0c             	add    esp,0xc
  543c6c:	eb 2c                	jmp    0x543c9a
  543c6e:	a1 70 63 5b 00       	mov    eax,ds:0x5b6370
  543c73:	0f 10 05 60 63 5b 00 	movups xmm0,XMMWORD PTR ds:0x5b6360
  543c7a:	8b b5 48 fa ff ff    	mov    esi,DWORD PTR [ebp-0x5b8]
  543c80:	89 85 08 fc ff ff    	mov    DWORD PTR [ebp-0x3f8],eax
  543c86:	66 a1 74 63 5b 00    	mov    ax,ds:0x5b6374
  543c8c:	0f 11 85 f8 fb ff ff 	movups XMMWORD PTR [ebp-0x408],xmm0
  543c93:	66 89 85 0c fc ff ff 	mov    WORD PTR [ebp-0x3f4],ax
  543c9a:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  543ca0:	c7 05 50 ba 5b 06 01 	mov    DWORD PTR ds:0x65bba50,0x1
  543ca7:	00 00 00 
  543caa:	e8 01 c6 fb ff       	call   0x5002b0
  543caf:	83 c0 d5             	add    eax,0xffffffd5
  543cb2:	c7 05 50 ba 5b 06 00 	mov    DWORD PTR ds:0x65bba50,0x0
  543cb9:	00 00 00 
  543cbc:	83 f8 28             	cmp    eax,0x28
  543cbf:	0f 87 42 03 00 00    	ja     0x544007
  543cc5:	0f b6 80 38 40 54 00 	movzx  eax,BYTE PTR [eax+0x544038]
  543ccc:	ff 24 85 18 40 54 00 	jmp    DWORD PTR [eax*4+0x544018]
  543cd3:	c6 85 67 fa ff ff 00 	mov    BYTE PTR [ebp-0x599],0x0
  543cda:	e9 d1 f7 ff ff       	jmp    0x5434b0
  543cdf:	c6 85 67 fa ff ff 01 	mov    BYTE PTR [ebp-0x599],0x1
  543ce6:	e9 c5 f7 ff ff       	jmp    0x5434b0
  543ceb:	80 bd 67 fa ff ff 00 	cmp    BYTE PTR [ebp-0x599],0x0
  543cf2:	74 32                	je     0x543d26
  543cf4:	8b 9d 4c fa ff ff    	mov    ebx,DWORD PTR [ebp-0x5b4]
  543cfa:	33 f6                	xor    esi,esi
  543cfc:	85 db                	test   ebx,ebx
  543cfe:	0f 8e 03 03 00 00    	jle    0x544007
  543d04:	8b 8c b5 68 fa ff ff 	mov    ecx,DWORD PTR [ebp+esi*4-0x598]
  543d0b:	e8 40 09 ee ff       	call   0x424650
  543d10:	46                   	inc    esi
  543d11:	3b f3                	cmp    esi,ebx
  543d13:	7c ef                	jl     0x543d04
  543d15:	5f                   	pop    edi
  543d16:	5e                   	pop    esi
  543d17:	5b                   	pop    ebx
  543d18:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  543d1b:	33 cd                	xor    ecx,ebp
  543d1d:	e8 8c 63 04 00       	call   0x58a0ae
  543d22:	8b e5                	mov    esp,ebp
  543d24:	5d                   	pop    ebp
  543d25:	c3                   	ret
  543d26:	8b ce                	mov    ecx,esi
  543d28:	e8 23 09 ee ff       	call   0x424650
  543d2d:	5f                   	pop    edi
  543d2e:	5e                   	pop    esi
  543d2f:	5b                   	pop    ebx
  543d30:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  543d33:	33 cd                	xor    ecx,ebp
  543d35:	e8 74 63 04 00       	call   0x58a0ae
  543d3a:	8b e5                	mov    esp,ebp
  543d3c:	5d                   	pop    ebp
  543d3d:	c3                   	ret
  543d3e:	8b ce                	mov    ecx,esi
  543d40:	e8 8b f4 ff ff       	call   0x5431d0
  543d45:	5f                   	pop    edi
  543d46:	5e                   	pop    esi
  543d47:	5b                   	pop    ebx
  543d48:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  543d4b:	33 cd                	xor    ecx,ebp
  543d4d:	e8 5c 63 04 00       	call   0x58a0ae
  543d52:	8b e5                	mov    esp,ebp
  543d54:	5d                   	pop    ebp
  543d55:	c3                   	ret
  543d56:	b9 78 63 5b 00       	mov    ecx,0x5b6378
  543d5b:	89 35 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,esi
  543d61:	e8 9a dd 01 00       	call   0x561b00
  543d66:	8b c8                	mov    ecx,eax
  543d68:	e8 a3 27 fb ff       	call   0x4f6510
  543d6d:	e8 ee 83 f4 ff       	call   0x48c160
  543d72:	85 c0                	test   eax,eax
  543d74:	75 6e                	jne    0x543de4
  543d76:	8b 8d 50 fa ff ff    	mov    ecx,DWORD PTR [ebp-0x5b0]
  543d7c:	8b 81 e4 15 15 06    	mov    eax,DWORD PTR [ecx+0x61515e4]
  543d82:	a9 00 02 00 00       	test   eax,0x200
  543d87:	75 05                	jne    0x543d8e
  543d89:	05 00 02 00 00       	add    eax,0x200
  543d8e:	89 81 e4 15 15 06    	mov    DWORD PTR [ecx+0x61515e4],eax
  543d94:	a1 e0 b8 72 0a       	mov    eax,ds:0xa72b8e0
  543d99:	83 c0 3c             	add    eax,0x3c
  543d9c:	89 81 20 19 15 06    	mov    DWORD PTR [ecx+0x6151920],eax
  543da2:	83 fe ff             	cmp    esi,0xffffffff
  543da5:	0f 84 5c 02 00 00    	je     0x544007
  543dab:	80 b9 00 14 15 06 01 	cmp    BYTE PTR [ecx+0x6151400],0x1
  543db2:	0f 84 4f 02 00 00    	je     0x544007
  543db8:	83 ca ff             	or     edx,0xffffffff
  543dbb:	8b ce                	mov    ecx,esi
  543dbd:	e8 ee c3 ed ff       	call   0x4201b0
  543dc2:	6a 3c                	push   0x3c
  543dc4:	ba 02 00 00 00       	mov    edx,0x2
  543dc9:	8b ce                	mov    ecx,esi
  543dcb:	e8 50 09 ee ff       	call   0x424720
  543dd0:	83 c4 04             	add    esp,0x4
  543dd3:	5f                   	pop    edi
  543dd4:	5e                   	pop    esi
  543dd5:	5b                   	pop    ebx
  543dd6:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  543dd9:	33 cd                	xor    ecx,ebp
  543ddb:	e8 ce 62 04 00       	call   0x58a0ae
  543de0:	8b e5                	mov    esp,ebp
  543de2:	5d                   	pop    ebp
  543de3:	c3                   	ret
  543de4:	83 fe ff             	cmp    esi,0xffffffff
  543de7:	74 19                	je     0x543e02
  543de9:	8b 8d 50 fa ff ff    	mov    ecx,DWORD PTR [ebp-0x5b0]
  543def:	80 b9 00 14 15 06 01 	cmp    BYTE PTR [ecx+0x6151400],0x1
  543df6:	74 0a                	je     0x543e02
  543df8:	b9 78 1c 59 00       	mov    ecx,0x591c78
  543dfd:	e9 a0 00 00 00       	jmp    0x543ea2
  543e02:	ba 8c 1c 59 00       	mov    edx,0x591c8c
  543e07:	8b ce                	mov    ecx,esi
  543e09:	e8 a2 1a ee ff       	call   0x4258b0
  543e0e:	5f                   	pop    edi
  543e0f:	5e                   	pop    esi
  543e10:	5b                   	pop    ebx
  543e11:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  543e14:	33 cd                	xor    ecx,ebp
  543e16:	e8 93 62 04 00       	call   0x58a0ae
  543e1b:	8b e5                	mov    esp,ebp
  543e1d:	5d                   	pop    ebp
  543e1e:	c3                   	ret
  543e1f:	b9 88 63 5b 00       	mov    ecx,0x5b6388
  543e24:	89 35 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,esi
  543e2a:	e8 d1 dc 01 00       	call   0x561b00
  543e2f:	8b c8                	mov    ecx,eax
  543e31:	e8 da 26 fb ff       	call   0x4f6510
  543e36:	8b 8d 50 fa ff ff    	mov    ecx,DWORD PTR [ebp-0x5b0]
  543e3c:	8b 81 e4 15 15 06    	mov    eax,DWORD PTR [ecx+0x61515e4]
  543e42:	a9 00 02 00 00       	test   eax,0x200
  543e47:	74 05                	je     0x543e4e
  543e49:	05 00 fe ff ff       	add    eax,0xfffffe00
  543e4e:	80 89 dd 15 15 06 04 	or     BYTE PTR [ecx+0x61515dd],0x4
  543e55:	89 81 e4 15 15 06    	mov    DWORD PTR [ecx+0x61515e4],eax
  543e5b:	b9 a0 1c 59 00       	mov    ecx,0x591ca0
  543e60:	69 c6 68 05 00 00    	imul   eax,esi,0x568
  543e66:	c7 80 7c 17 15 06 00 	mov    DWORD PTR [eax+0x615177c],0x0
  543e6d:	00 00 00 
  543e70:	c7 80 a4 17 15 06 00 	mov    DWORD PTR [eax+0x61517a4],0x0
  543e77:	00 00 00 
  543e7a:	c7 80 e4 18 15 06 00 	mov    DWORD PTR [eax+0x61518e4],0x0
  543e81:	00 00 00 
  543e84:	c7 80 6c 18 15 06 00 	mov    DWORD PTR [eax+0x615186c],0x0
  543e8b:	00 00 00 
  543e8e:	c7 80 94 18 15 06 00 	mov    DWORD PTR [eax+0x6151894],0x0
  543e95:	00 00 00 
  543e98:	c7 80 bc 18 15 06 00 	mov    DWORD PTR [eax+0x61518bc],0x0
  543e9f:	00 00 00 
  543ea2:	68 16 c6 58 00       	push   0x58c616
  543ea7:	89 35 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,esi
  543ead:	e8 4e dc 01 00       	call   0x561b00
  543eb2:	8b d0                	mov    edx,eax
  543eb4:	8b ce                	mov    ecx,esi
  543eb6:	e8 f5 9d fb ff       	call   0x4fdcb0
  543ebb:	83 c4 04             	add    esp,0x4
  543ebe:	5f                   	pop    edi
  543ebf:	5e                   	pop    esi
  543ec0:	5b                   	pop    ebx
  543ec1:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  543ec4:	33 cd                	xor    ecx,ebp
  543ec6:	e8 e3 61 04 00       	call   0x58a0ae
  543ecb:	8b e5                	mov    esp,ebp
  543ecd:	5d                   	pop    ebp
  543ece:	c3                   	ret
  543ecf:	80 bd 67 fa ff ff 00 	cmp    BYTE PTR [ebp-0x599],0x0
  543ed6:	74 4e                	je     0x543f26
  543ed8:	8b bd 4c fa ff ff    	mov    edi,DWORD PTR [ebp-0x5b4]
  543ede:	33 f6                	xor    esi,esi
  543ee0:	85 ff                	test   edi,edi
  543ee2:	7e 22                	jle    0x543f06
  543ee4:	8b 84 b5 68 fa ff ff 	mov    eax,DWORD PTR [ebp+esi*4-0x598]
  543eeb:	b9 98 63 5b 00       	mov    ecx,0x5b6398
  543ef0:	a3 4c 2a 62 0a       	mov    ds:0xa622a4c,eax
  543ef5:	e8 06 dc 01 00       	call   0x561b00
  543efa:	8b c8                	mov    ecx,eax
  543efc:	e8 0f 26 fb ff       	call   0x4f6510
  543f01:	46                   	inc    esi
  543f02:	3b f7                	cmp    esi,edi
  543f04:	7c de                	jl     0x543ee4
  543f06:	8b b5 48 fa ff ff    	mov    esi,DWORD PTR [ebp-0x5b8]
  543f0c:	ba 16 c6 58 00       	mov    edx,0x58c616
  543f11:	b1 01                	mov    cl,0x1
  543f13:	e8 08 39 fb ff       	call   0x4f7820
  543f18:	84 c0                	test   al,al
  543f1a:	75 29                	jne    0x543f45
  543f1c:	b9 f0 5e 59 00       	mov    ecx,0x595ef0
  543f21:	e9 dc 00 00 00       	jmp    0x544002
  543f26:	b9 98 63 5b 00       	mov    ecx,0x5b6398
  543f2b:	89 35 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,esi
  543f31:	e8 ca db 01 00       	call   0x561b00
  543f36:	8b c8                	mov    ecx,eax
  543f38:	e8 d3 25 fb ff       	call   0x4f6510
  543f3d:	8b bd 4c fa ff ff    	mov    edi,DWORD PTR [ebp-0x5b4]
  543f43:	eb c7                	jmp    0x543f0c
  543f45:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  543f4b:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c
  543f51:	e8 ca 51 ed ff       	call   0x419120
  543f56:	8b d8                	mov    ebx,eax
  543f58:	83 fb ff             	cmp    ebx,0xffffffff
  543f5b:	75 0a                	jne    0x543f67
  543f5d:	b9 ac 63 5b 00       	mov    ecx,0x5b63ac
  543f62:	e9 94 00 00 00       	jmp    0x543ffb
  543f67:	80 bd 67 fa ff ff 00 	cmp    BYTE PTR [ebp-0x599],0x0
  543f6e:	74 51                	je     0x543fc1
  543f70:	33 f6                	xor    esi,esi
  543f72:	85 ff                	test   edi,edi
  543f74:	0f 8e 8d 00 00 00    	jle    0x544007
  543f7a:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  543f80:	8b bc b5 68 fa ff ff 	mov    edi,DWORD PTR [ebp+esi*4-0x598]
  543f87:	8b d7                	mov    edx,edi
  543f89:	53                   	push   ebx
  543f8a:	e8 91 f6 fe ff       	call   0x533620
  543f8f:	83 c4 04             	add    esp,0x4
  543f92:	85 c0                	test   eax,eax
  543f94:	74 11                	je     0x543fa7
  543f96:	68 c8 00 00 00       	push   0xc8
  543f9b:	8b d3                	mov    edx,ebx
  543f9d:	8b cf                	mov    ecx,edi
  543f9f:	e8 3c e9 fe ff       	call   0x5328e0
  543fa4:	83 c4 04             	add    esp,0x4
  543fa7:	46                   	inc    esi
  543fa8:	3b b5 4c fa ff ff    	cmp    esi,DWORD PTR [ebp-0x5b4]
  543fae:	7c d0                	jl     0x543f80
  543fb0:	5f                   	pop    edi
  543fb1:	5e                   	pop    esi
  543fb2:	5b                   	pop    ebx
  543fb3:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  543fb6:	33 cd                	xor    ecx,ebp
  543fb8:	e8 f1 60 04 00       	call   0x58a0ae
  543fbd:	8b e5                	mov    esp,ebp
  543fbf:	5d                   	pop    ebp
  543fc0:	c3                   	ret
  543fc1:	53                   	push   ebx
  543fc2:	8b d6                	mov    edx,esi
  543fc4:	e8 57 f6 fe ff       	call   0x533620
  543fc9:	83 c4 04             	add    esp,0x4
  543fcc:	85 c0                	test   eax,eax
  543fce:	74 37                	je     0x544007
  543fd0:	68 c8 00 00 00       	push   0xc8
  543fd5:	8b d3                	mov    edx,ebx
  543fd7:	8b ce                	mov    ecx,esi
  543fd9:	e8 02 e9 fe ff       	call   0x5328e0
  543fde:	83 c4 04             	add    esp,0x4
  543fe1:	5f                   	pop    edi
  543fe2:	5e                   	pop    esi
  543fe3:	5b                   	pop    ebx
  543fe4:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  543fe7:	33 cd                	xor    ecx,ebp
  543fe9:	e8 c0 60 04 00       	call   0x58a0ae
  543fee:	8b e5                	mov    esp,ebp
  543ff0:	5d                   	pop    ebp
  543ff1:	c3                   	ret
  543ff2:	85 db                	test   ebx,ebx
  543ff4:	75 11                	jne    0x544007
  543ff6:	b9 c0 63 5b 00       	mov    ecx,0x5b63c0
  543ffb:	e8 00 db 01 00       	call   0x561b00
  544000:	8b c8                	mov    ecx,eax
  544002:	e8 09 25 fb ff       	call   0x4f6510
  544007:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  54400a:	5f                   	pop    edi
  54400b:	5e                   	pop    esi
  54400c:	33 cd                	xor    ecx,ebp
  54400e:	5b                   	pop    ebx
  54400f:	e8                   	.byte 0xe8
