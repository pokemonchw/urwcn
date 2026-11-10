
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0050e3e0 <.text+0x10d3e0>:
  50e3e0:	55                   	push   ebp
  50e3e1:	8b ec                	mov    ebp,esp
  50e3e3:	81 ec 44 01 00 00    	sub    esp,0x144
  50e3e9:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  50e3ee:	33 c5                	xor    eax,ebp
  50e3f0:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  50e3f3:	53                   	push   ebx
  50e3f4:	56                   	push   esi
  50e3f5:	57                   	push   edi
  50e3f6:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  50e3fc:	8b da                	mov    ebx,edx
  50e3fe:	ff 15 6c c2 58 00    	call   DWORD PTR ds:0x58c26c
  50e404:	83 c4 04             	add    esp,0x4
  50e407:	89 85 c0 fe ff ff    	mov    DWORD PTR [ebp-0x140],eax
  50e40d:	6a 00                	push   0x0
  50e40f:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  50e415:	ff 15 88 c2 58 00    	call   DWORD PTR ds:0x58c288
  50e41b:	8b 4d 0c             	mov    ecx,DWORD PTR [ebp+0xc]
  50e41e:	8d 95 c8 fe ff ff    	lea    edx,[ebp-0x138]
  50e424:	83 c4 08             	add    esp,0x8
  50e427:	2b d1                	sub    edx,ecx
  50e429:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  50e430:	8a 01                	mov    al,BYTE PTR [ecx]
  50e432:	8d 49 01             	lea    ecx,[ecx+0x1]
  50e435:	88 44 0a ff          	mov    BYTE PTR [edx+ecx*1-0x1],al
  50e439:	84 c0                	test   al,al
  50e43b:	75 f3                	jne    0x50e430
  50e43d:	8d 8d c8 fe ff ff    	lea    ecx,[ebp-0x138]
  50e443:	c7 85 c4 fe ff ff 00 	mov    DWORD PTR [ebp-0x13c],0xff000000
  50e44a:	00 00 ff 
  50e44d:	33 d2                	xor    edx,edx
  50e44f:	8d 71 01             	lea    esi,[ecx+0x1]
  50e452:	8a 01                	mov    al,BYTE PTR [ecx]
  50e454:	41                   	inc    ecx
  50e455:	84 c0                	test   al,al
  50e457:	75 f9                	jne    0x50e452
  50e459:	2b ce                	sub    ecx,esi
  50e45b:	74 46                	je     0x50e4a3
  50e45d:	0f 1f 00             	nop    DWORD PTR [eax]
  50e460:	8a 8c 15 c8 fe ff ff 	mov    cl,BYTE PTR [ebp+edx*1-0x138]
  50e467:	0f b6 c1             	movzx  eax,cl
  50e46a:	2d c4 00 00 00       	sub    eax,0xc4
  50e46f:	74 12                	je     0x50e483
  50e471:	83 e8 20             	sub    eax,0x20
  50e474:	74 09                	je     0x50e47f
  50e476:	83 e8 12             	sub    eax,0x12
  50e479:	75 0a                	jne    0x50e485
  50e47b:	b1 94                	mov    cl,0x94
  50e47d:	eb 06                	jmp    0x50e485
  50e47f:	b1 84                	mov    cl,0x84
  50e481:	eb 02                	jmp    0x50e485
  50e483:	b1 8e                	mov    cl,0x8e
  50e485:	8d 85 c8 fe ff ff    	lea    eax,[ebp-0x138]
  50e48b:	88 8c 15 c8 fe ff ff 	mov    BYTE PTR [ebp+edx*1-0x138],cl
  50e492:	42                   	inc    edx
  50e493:	8d 70 01             	lea    esi,[eax+0x1]
  50e496:	8a 08                	mov    cl,BYTE PTR [eax]
  50e498:	40                   	inc    eax
  50e499:	84 c9                	test   cl,cl
  50e49b:	75 f9                	jne    0x50e496
  50e49d:	2b c6                	sub    eax,esi
  50e49f:	3b d0                	cmp    edx,eax
  50e4a1:	72 bd                	jb     0x50e460
  50e4a3:	8b 7d 08             	mov    edi,DWORD PTR [ebp+0x8]
  50e4a6:	8d 85 c8 fe ff ff    	lea    eax,[ebp-0x138]
  50e4ac:	8b b5 c4 fe ff ff    	mov    esi,DWORD PTR [ebp-0x13c]
  50e4b2:	8b d3                	mov    edx,ebx
  50e4b4:	51                   	push   ecx
  50e4b5:	56                   	push   esi
  50e4b6:	50                   	push   eax
  50e4b7:	8d 47 ff             	lea    eax,[edi-0x1]
  50e4ba:	50                   	push   eax
  50e4bb:	e8 b0 fc ff ff       	call   0x50e170
  50e4c0:	83 c4 0c             	add    esp,0xc
  50e4c3:	8d 85 c8 fe ff ff    	lea    eax,[ebp-0x138]
  50e4c9:	8b d3                	mov    edx,ebx
  50e4cb:	56                   	push   esi
  50e4cc:	50                   	push   eax
  50e4cd:	8d 47 01             	lea    eax,[edi+0x1]
  50e4d0:	50                   	push   eax
  50e4d1:	e8 9a fc ff ff       	call   0x50e170
  50e4d6:	83 c4 0c             	add    esp,0xc
  50e4d9:	8d 85 c8 fe ff ff    	lea    eax,[ebp-0x138]
  50e4df:	8d 53 ff             	lea    edx,[ebx-0x1]
  50e4e2:	56                   	push   esi
  50e4e3:	50                   	push   eax
  50e4e4:	57                   	push   edi
  50e4e5:	e8 86 fc ff ff       	call   0x50e170
  50e4ea:	83 c4 0c             	add    esp,0xc
  50e4ed:	8d 85 c8 fe ff ff    	lea    eax,[ebp-0x138]
  50e4f3:	8d 53 01             	lea    edx,[ebx+0x1]
  50e4f6:	56                   	push   esi
  50e4f7:	50                   	push   eax
  50e4f8:	57                   	push   edi
  50e4f9:	e8 72 fc ff ff       	call   0x50e170
  50e4fe:	83 c4 0c             	add    esp,0xc
  50e501:	8d 85 c8 fe ff ff    	lea    eax,[ebp-0x138]
  50e507:	8b d3                	mov    edx,ebx
  50e509:	ff 75 10             	push   DWORD PTR [ebp+0x10]
  50e50c:	50                   	push   eax
  50e50d:	57                   	push   edi
  50e50e:	e8 5d fc ff ff       	call   0x50e170
  50e513:	ff b5 c0 fe ff ff    	push   DWORD PTR [ebp-0x140]
  50e519:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  50e51f:	ff 15 88 c2 58 00    	call   DWORD PTR ds:0x58c288
  50e525:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  50e528:	83 c4 18             	add    esp,0x18
  50e52b:	33 cd                	xor    ecx,ebp
  50e52d:	5f                   	pop    edi
  50e52e:	5e                   	pop    esi
  50e52f:	5b                   	pop    ebx
  50e530:	e8 79 bb 07 00       	call   0x58a0ae
  50e535:	8b e5                	mov    esp,ebp
  50e537:	5d                   	pop    ebp
  50e538:	c3                   	ret
  50e539:	cc                   	int3
