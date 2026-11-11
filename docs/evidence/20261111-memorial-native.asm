
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004dd400 <.text+0xdc400>:
  4dd400:	55                   	push   ebp
  4dd401:	8b ec                	mov    ebp,esp
  4dd403:	83 e4 c0             	and    esp,0xffffffc0
  4dd406:	b8 34 30 00 00       	mov    eax,0x3034
  4dd40b:	e8 c0 dc 0a 00       	call   0x58b0d0
  4dd410:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4dd415:	33 c4                	xor    eax,esp
  4dd417:	89 84 24 30 30 00 00 	mov    DWORD PTR [esp+0x3030],eax
  4dd41e:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4dd423:	53                   	push   ebx
  4dd424:	8b 1d f8 c1 58 00    	mov    ebx,DWORD PTR ds:0x58c1f8
  4dd42a:	56                   	push   esi
  4dd42b:	8b 75 08             	mov    esi,DWORD PTR [ebp+0x8]
  4dd42e:	57                   	push   edi
  4dd42f:	68 8c 00 00 00       	push   0x8c
  4dd434:	68 e6 00 00 00       	push   0xe6
  4dd439:	68 f0 00 00 00       	push   0xf0
  4dd43e:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4dd441:	89 54 24 48          	mov    DWORD PTR [esp+0x48],edx
  4dd445:	ff d3                	call   ebx
  4dd447:	56                   	push   esi
  4dd448:	89 44 24 50          	mov    DWORD PTR [esp+0x50],eax
  4dd44c:	8d 84 24 4c 1c 00 00 	lea    eax,[esp+0x1c4c]
  4dd453:	68 70 62 5a 00       	push   0x5a6270
  4dd458:	50                   	push   eax
  4dd459:	e8 72 3c f2 ff       	call   0x4010d0
  4dd45e:	83 c4 1c             	add    esp,0x1c
  4dd461:	8d 84 24 38 1c 00 00 	lea    eax,[esp+0x1c38]
  4dd468:	50                   	push   eax
  4dd469:	8d 84 24 3c 18 00 00 	lea    eax,[esp+0x183c]
  4dd470:	68 80 62 5a 00       	push   0x5a6280
  4dd475:	50                   	push   eax
  4dd476:	e8 55 3c f2 ff       	call   0x4010d0
  4dd47b:	83 c4 0c             	add    esp,0xc
  4dd47e:	8d 84 24 38 18 00 00 	lea    eax,[esp+0x1838]
  4dd485:	68 08 f7 58 00       	push   0x58f708
  4dd48a:	50                   	push   eax
  4dd48b:	ff 15 78 c4 58 00    	call   DWORD PTR ds:0x58c478
  4dd491:	8b f0                	mov    esi,eax
  4dd493:	83 c4 08             	add    esp,0x8
  4dd496:	85 f6                	test   esi,esi
  4dd498:	0f 84 b4 05 00 00    	je     0x4dda52
  4dd49e:	56                   	push   esi
  4dd49f:	ba 00 04 00 00       	mov    edx,0x400
  4dd4a4:	8d 8c 24 3c 2c 00 00 	lea    ecx,[esp+0x2c3c]
  4dd4ab:	e8 d0 6d ff ff       	call   0x4d4280
  4dd4b0:	8b 3d b4 c4 58 00    	mov    edi,DWORD PTR ds:0x58c4b4
  4dd4b6:	83 c4 04             	add    esp,0x4
  4dd4b9:	56                   	push   esi
  4dd4ba:	ff d7                	call   edi
  4dd4bc:	83 c4 04             	add    esp,0x4
  4dd4bf:	8d 84 24 38 2c 00 00 	lea    eax,[esp+0x2c38]
  4dd4c6:	50                   	push   eax
  4dd4c7:	8d 84 24 3c 1c 00 00 	lea    eax,[esp+0x1c3c]
  4dd4ce:	50                   	push   eax
  4dd4cf:	8d 84 24 40 18 00 00 	lea    eax,[esp+0x1840]
  4dd4d6:	68 90 62 5a 00       	push   0x5a6290
  4dd4db:	50                   	push   eax
  4dd4dc:	e8 ef 3b f2 ff       	call   0x4010d0
  4dd4e1:	8d 84 24 48 18 00 00 	lea    eax,[esp+0x1848]
  4dd4e8:	68 f8 f1 58 00       	push   0x58f1f8
  4dd4ed:	50                   	push   eax
  4dd4ee:	ff 15 78 c4 58 00    	call   DWORD PTR ds:0x58c478
  4dd4f4:	8b f0                	mov    esi,eax
  4dd4f6:	83 c4 18             	add    esp,0x18
  4dd4f9:	85 f6                	test   esi,esi
  4dd4fb:	0f 84 51 05 00 00    	je     0x4dda52
  4dd501:	56                   	push   esi
  4dd502:	6a 01                	push   0x1
  4dd504:	68 58 56 00 00       	push   0x5658
  4dd509:	68 48 56 35 06       	push   0x6355648
  4dd50e:	ff 15 a8 c4 58 00    	call   DWORD PTR ds:0x58c4a8
  4dd514:	56                   	push   esi
  4dd515:	ff d7                	call   edi
  4dd517:	83 c4 14             	add    esp,0x14
  4dd51a:	8d 84 24 10 01 00 00 	lea    eax,[esp+0x110]
  4dd521:	68 54 16 00 00       	push   0x1654
  4dd526:	68 e8 a6 72 0a       	push   0xa72a6e8
  4dd52b:	50                   	push   eax
  4dd52c:	e8 6f e0 0a 00       	call   0x58b5a0
  4dd531:	83 c4 0c             	add    esp,0xc
  4dd534:	68 54 16 00 00       	push   0x1654
  4dd539:	68 4c 96 35 06       	push   0x635964c
  4dd53e:	68 e8 a6 72 0a       	push   0xa72a6e8
  4dd543:	e8 58 e0 0a 00       	call   0x58b5a0
  4dd548:	83 c4 0c             	add    esp,0xc
  4dd54b:	80 7d 0c 00          	cmp    BYTE PTR [ebp+0xc],0x0
  4dd54f:	74 64                	je     0x4dd5b5
  4dd551:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4dd556:	6a 54                	push   0x54
  4dd558:	68 fc 00 00 00       	push   0xfc
  4dd55d:	68 fc 00 00 00       	push   0xfc
  4dd562:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4dd565:	ff d3                	call   ebx
  4dd567:	8b 0d 10 bb 5b 06    	mov    ecx,DWORD PTR ds:0x65bbb10
  4dd56d:	8b f0                	mov    esi,eax
  4dd56f:	68 98 00 00 00       	push   0x98
  4dd574:	6a 5a                	push   0x5a
  4dd576:	6a 3c                	push   0x3c
  4dd578:	ff 71 04             	push   DWORD PTR [ecx+0x4]
  4dd57b:	ff d3                	call   ebx
  4dd57d:	05 00 10 00 00       	add    eax,0x1000
  4dd582:	ba 05 00 00 00       	mov    edx,0x5
  4dd587:	50                   	push   eax
  4dd588:	68 16 c6 58 00       	push   0x58c616
  4dd58d:	6a 10                	push   0x10
  4dd58f:	68 16 03 00 00       	push   0x316
  4dd594:	8b ca                	mov    ecx,edx
  4dd596:	e8 d5 88 03 00       	call   0x515e70
  4dd59b:	6a 01                	push   0x1
  4dd59d:	56                   	push   esi
  4dd59e:	68 9c 62 5a 00       	push   0x5a629c
  4dd5a3:	ba 09 00 00 00       	mov    edx,0x9
  4dd5a8:	b9 61 01 00 00       	mov    ecx,0x161
  4dd5ad:	e8 ee 0f 03 00       	call   0x50e5a0
  4dd5b2:	83 c4 3c             	add    esp,0x3c
  4dd5b5:	b9 ac 62 5a 00       	mov    ecx,0x5a62ac
  4dd5ba:	e8 41 45 08 00       	call   0x561b00
  4dd5bf:	8d 94 24 68 17 00 00 	lea    edx,[esp+0x1768]
  4dd5c6:	2b d0                	sub    edx,eax
  4dd5c8:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  4dd5cf:	00 
  4dd5d0:	8a 08                	mov    cl,BYTE PTR [eax]
  4dd5d2:	8d 40 01             	lea    eax,[eax+0x1]
  4dd5d5:	88 4c 10 ff          	mov    BYTE PTR [eax+edx*1-0x1],cl
  4dd5d9:	84 c9                	test   cl,cl
  4dd5db:	75 f3                	jne    0x4dd5d0
  4dd5dd:	b9 bc 62 5a 00       	mov    ecx,0x5a62bc
  4dd5e2:	e8 19 45 08 00       	call   0x561b00
  4dd5e7:	8d 94 24 d0 17 00 00 	lea    edx,[esp+0x17d0]
  4dd5ee:	2b d0                	sub    edx,eax
  4dd5f0:	8a 08                	mov    cl,BYTE PTR [eax]
  4dd5f2:	8d 40 01             	lea    eax,[eax+0x1]
  4dd5f5:	88 4c 10 ff          	mov    BYTE PTR [eax+edx*1-0x1],cl
  4dd5f9:	84 c9                	test   cl,cl
  4dd5fb:	75 f3                	jne    0x4dd5f0
  4dd5fd:	80 3d a9 b1 72 0a 02 	cmp    BYTE PTR ds:0xa72b1a9,0x2
  4dd604:	75 47                	jne    0x4dd64d
  4dd606:	b9 c8 62 5a 00       	mov    ecx,0x5a62c8
  4dd60b:	e8 f0 44 08 00       	call   0x561b00
  4dd610:	8d 94 24 68 17 00 00 	lea    edx,[esp+0x1768]
  4dd617:	2b d0                	sub    edx,eax
  4dd619:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  4dd620:	8a 08                	mov    cl,BYTE PTR [eax]
  4dd622:	8d 40 01             	lea    eax,[eax+0x1]
  4dd625:	88 4c 10 ff          	mov    BYTE PTR [eax+edx*1-0x1],cl
  4dd629:	84 c9                	test   cl,cl
  4dd62b:	75 f3                	jne    0x4dd620
  4dd62d:	b9 d4 62 5a 00       	mov    ecx,0x5a62d4
  4dd632:	e8 c9 44 08 00       	call   0x561b00
  4dd637:	8d 94 24 d0 17 00 00 	lea    edx,[esp+0x17d0]
  4dd63e:	2b d0                	sub    edx,eax
  4dd640:	8a 08                	mov    cl,BYTE PTR [eax]
  4dd642:	8d 40 01             	lea    eax,[eax+0x1]
  4dd645:	88 4c 10 ff          	mov    BYTE PTR [eax+edx*1-0x1],cl
  4dd649:	84 c9                	test   cl,cl
  4dd64b:	75 f3                	jne    0x4dd640
  4dd64d:	ff 35 28 a1 35 06    	push   DWORD PTR ds:0x635a128
  4dd653:	0f b6 05 1d a1 35 06 	movzx  eax,BYTE PTR ds:0x635a11d
  4dd65a:	50                   	push   eax
  4dd65b:	8d 84 24 70 17 00 00 	lea    eax,[esp+0x1770]
  4dd662:	50                   	push   eax
  4dd663:	8d 84 24 44 24 00 00 	lea    eax,[esp+0x2444]
  4dd66a:	68 e0 62 5a 00       	push   0x5a62e0
  4dd66f:	50                   	push   eax
  4dd670:	e8 5b 3a f2 ff       	call   0x4010d0
  4dd675:	0f b6 84 24 4c 24 00 	movzx  eax,BYTE PTR [esp+0x244c]
  4dd67c:	00 
  4dd67d:	83 c4 14             	add    esp,0x14
  4dd680:	8b 35 e8 c4 58 00    	mov    esi,DWORD PTR ds:0x58c4e8
  4dd686:	50                   	push   eax
  4dd687:	ff d6                	call   esi
  4dd689:	f3 0f 10 05 dc b0 72 	movss  xmm0,DWORD PTR ds:0xa72b0dc
  4dd690:	0a 
  4dd691:	0f 5a c0             	cvtps2pd xmm0,xmm0
  4dd694:	51                   	push   ecx
  4dd695:	88 84 24 40 24 00 00 	mov    BYTE PTR [esp+0x2440],al
  4dd69c:	f2 0f 11 44 24 30    	movsd  QWORD PTR [esp+0x30],xmm0
  4dd6a2:	dd 44 24 30          	fld    QWORD PTR [esp+0x30]
  4dd6a6:	dd 1c 24             	fstp   QWORD PTR [esp]
  4dd6a9:	e8 34 df 0a 00       	call   0x58b5e2
  4dd6ae:	dd 5c 24 30          	fstp   QWORD PTR [esp+0x30]
  4dd6b2:	f2 0f 10 44 24 30    	movsd  xmm0,QWORD PTR [esp+0x30]
  4dd6b8:	66 0f 5a c0          	cvtpd2ps xmm0,xmm0
  4dd6bc:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4dd6c0:	50                   	push   eax
  4dd6c1:	8d 84 24 74 17 00 00 	lea    eax,[esp+0x1774]
  4dd6c8:	50                   	push   eax
  4dd6c9:	8d 84 24 48 28 00 00 	lea    eax,[esp+0x2848]
  4dd6d0:	68 28 63 5a 00       	push   0x5a6328
  4dd6d5:	50                   	push   eax
  4dd6d6:	e8 f5 39 f2 ff       	call   0x4010d0
  4dd6db:	0f b6 84 24 50 28 00 	movzx  eax,BYTE PTR [esp+0x2850]
  4dd6e2:	00 
  4dd6e3:	50                   	push   eax
  4dd6e4:	ff d6                	call   esi
  4dd6e6:	83 c4 1c             	add    esp,0x1c
  4dd6e9:	88 84 24 38 28 00 00 	mov    BYTE PTR [esp+0x2838],al
  4dd6f0:	8d 84 24 38 1c 00 00 	lea    eax,[esp+0x1c38]
  4dd6f7:	50                   	push   eax
  4dd6f8:	8d 84 24 3c 18 00 00 	lea    eax,[esp+0x183c]
  4dd6ff:	68 70 f4 58 00       	push   0x58f470
  4dd704:	50                   	push   eax
  4dd705:	e8 c6 39 f2 ff       	call   0x4010d0
  4dd70a:	83 c4 0c             	add    esp,0xc
  4dd70d:	80 7d 0c 00          	cmp    BYTE PTR [ebp+0xc],0x0
  4dd711:	74 11                	je     0x4dd724
  4dd713:	b9 58 63 5a 00       	mov    ecx,0x5a6358
  4dd718:	e8 33 db 02 00       	call   0x50b250
  4dd71d:	be c8 00 00 00       	mov    esi,0xc8
  4dd722:	eb 17                	jmp    0x4dd73b
  4dd724:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4dd72b:	00 
  4dd72c:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4dd72f:	f3 0f 59 05 38 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd538
  4dd736:	00 
  4dd737:	f3 0f 2c f0          	cvttss2si esi,xmm0
  4dd73b:	6a 01                	push   0x1
  4dd73d:	51                   	push   ecx
  4dd73e:	8d 94 24 40 18 00 00 	lea    edx,[esp+0x1840]
  4dd745:	89 74 24 3c          	mov    DWORD PTR [esp+0x3c],esi
  4dd749:	8d 7e 14             	lea    edi,[esi+0x14]
  4dd74c:	8b ca                	mov    ecx,edx
  4dd74e:	68 58 63 5a 00       	push   0x5a6358
  4dd753:	89 7c 24 34          	mov    DWORD PTR [esp+0x34],edi
  4dd757:	e8 b4 94 03 00       	call   0x516c10
  4dd75c:	8b 4c 24 44          	mov    ecx,DWORD PTR [esp+0x44]
  4dd760:	83 c4 0c             	add    esp,0xc
  4dd763:	69 c0 48 0c 00 00    	imul   eax,eax,0xc48
  4dd769:	6a 54                	push   0x54
  4dd76b:	68 fc 00 00 00       	push   0xfc
  4dd770:	68 fc 00 00 00       	push   0xfc
  4dd775:	89 88 20 52 78 0a    	mov    DWORD PTR [eax+0xa785220],ecx
  4dd77b:	8b ce                	mov    ecx,esi
  4dd77d:	c7 80 1c 52 78 0a 0a 	mov    DWORD PTR [eax+0xa78521c],0xa
  4dd784:	00 00 00 
  4dd787:	89 b0 24 52 78 0a    	mov    DWORD PTR [eax+0xa785224],esi
  4dd78d:	89 88 28 52 78 0a    	mov    DWORD PTR [eax+0xa785228],ecx
  4dd793:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4dd798:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4dd79b:	ff d3                	call   ebx
  4dd79d:	83 c4 10             	add    esp,0x10
  4dd7a0:	6a 01                	push   0x1
  4dd7a2:	50                   	push   eax
  4dd7a3:	e8 18 08 08 00       	call   0x55dfc0
  4dd7a8:	8b 54 24 40          	mov    edx,DWORD PTR [esp+0x40]
  4dd7ac:	8b cf                	mov    ecx,edi
  4dd7ae:	50                   	push   eax
  4dd7af:	e8 ec 0d 03 00       	call   0x50e5a0
  4dd7b4:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4dd7bb:	00 
  4dd7bc:	8d 84 24 44 18 00 00 	lea    eax,[esp+0x1844]
  4dd7c3:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4dd7c6:	83 c4 0c             	add    esp,0xc
  4dd7c9:	68 48 56 35 06       	push   0x6355648
  4dd7ce:	f3 0f 2c d8          	cvttss2si ebx,xmm0
  4dd7d2:	68 64 63 5a 00       	push   0x5a6364
  4dd7d7:	50                   	push   eax
  4dd7d8:	03 5c 24 44          	add    ebx,DWORD PTR [esp+0x44]
  4dd7dc:	e8 ef 38 f2 ff       	call   0x4010d0
  4dd7e1:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4dd7e6:	83 c4 0c             	add    esp,0xc
  4dd7e9:	68 ff 00 00 00       	push   0xff
  4dd7ee:	68 ff 00 00 00       	push   0xff
  4dd7f3:	68 ff 00 00 00       	push   0xff
  4dd7f8:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4dd7fb:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4dd801:	0f b6 8c 24 48 18 00 	movzx  ecx,BYTE PTR [esp+0x1848]
  4dd808:	00 
  4dd809:	8b f0                	mov    esi,eax
  4dd80b:	51                   	push   ecx
  4dd80c:	ff 15 e8 c4 58 00    	call   DWORD PTR ds:0x58c4e8
  4dd812:	83 c4 14             	add    esp,0x14
  4dd815:	88 84 24 38 18 00 00 	mov    BYTE PTR [esp+0x1838],al
  4dd81c:	8d 84 24 38 18 00 00 	lea    eax,[esp+0x1838]
  4dd823:	8b d3                	mov    edx,ebx
  4dd825:	8b cf                	mov    ecx,edi
  4dd827:	6a 01                	push   0x1
  4dd829:	56                   	push   esi
  4dd82a:	50                   	push   eax
  4dd82b:	e8 70 0d 03 00       	call   0x50e5a0
  4dd830:	f3 0f 10 0d 80 d3 5d 	movss  xmm1,DWORD PTR ds:0x5dd380
  4dd837:	00 
  4dd838:	83 c4 0c             	add    esp,0xc
  4dd83b:	80 7d 0c 00          	cmp    BYTE PTR [ebp+0xc],0x0
  4dd83f:	0f 84 9d 01 00 00    	je     0x4dd9e2
  4dd845:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4dd84c:	00 
  4dd84d:	0f b6 15 1c a1 35 06 	movzx  edx,BYTE PTR ds:0x635a11c
  4dd854:	0f b6 0d 10 a1 35 06 	movzx  ecx,BYTE PTR ds:0x635a110
  4dd85b:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4dd85e:	f3 0f 59 c1          	mulss  xmm0,xmm1
  4dd862:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4dd866:	03 d8                	add    ebx,eax
  4dd868:	8d 44 24 40          	lea    eax,[esp+0x40]
  4dd86c:	50                   	push   eax
  4dd86d:	e8 8e cd fa ff       	call   0x48a600
  4dd872:	81 ec cc 00 00 00    	sub    esp,0xcc
  4dd878:	8b f0                	mov    esi,eax
  4dd87a:	b9 33 00 00 00       	mov    ecx,0x33
  4dd87f:	8b fc                	mov    edi,esp
  4dd881:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  4dd883:	b9 22 00 00 00       	mov    ecx,0x22
  4dd888:	66 a5                	movs   WORD PTR es:[edi],WORD PTR ds:[esi]
  4dd88a:	a4                   	movs   BYTE PTR es:[edi],BYTE PTR ds:[esi]
  4dd88b:	e8 80 ca fa ff       	call   0x48a310
  4dd890:	50                   	push   eax
  4dd891:	8d 84 24 a4 18 00 00 	lea    eax,[esp+0x18a4]
  4dd898:	50                   	push   eax
  4dd899:	8d 84 24 40 18 00 00 	lea    eax,[esp+0x1840]
  4dd8a0:	50                   	push   eax
  4dd8a1:	8d 84 24 14 19 00 00 	lea    eax,[esp+0x1914]
  4dd8a8:	68 68 63 5a 00       	push   0x5a6368
  4dd8ad:	50                   	push   eax
  4dd8ae:	e8 1d 38 f2 ff       	call   0x4010d0
  4dd8b3:	0f b6 84 24 1c 19 00 	movzx  eax,BYTE PTR [esp+0x191c]
  4dd8ba:	00 
  4dd8bb:	81 c4 e4 00 00 00    	add    esp,0xe4
  4dd8c1:	50                   	push   eax
  4dd8c2:	ff 15 e8 c4 58 00    	call   DWORD PTR ds:0x58c4e8
  4dd8c8:	83 c4 04             	add    esp,0x4
  4dd8cb:	88 84 24 38 18 00 00 	mov    BYTE PTR [esp+0x1838],al
  4dd8d2:	8d 94 24 38 18 00 00 	lea    edx,[esp+0x1838]
  4dd8d9:	b9 01 00 00 00       	mov    ecx,0x1
  4dd8de:	e8 1d 4a 08 00       	call   0x562300
  4dd8e3:	8b 7c 24 28          	mov    edi,DWORD PTR [esp+0x28]
  4dd8e7:	b8 16 03 00 00       	mov    eax,0x316
  4dd8ec:	8b 74 24 3c          	mov    esi,DWORD PTR [esp+0x3c]
  4dd8f0:	2b c7                	sub    eax,edi
  4dd8f2:	6a 01                	push   0x1
  4dd8f4:	56                   	push   esi
  4dd8f5:	6a 64                	push   0x64
  4dd8f7:	50                   	push   eax
  4dd8f8:	8b d3                	mov    edx,ebx
  4dd8fa:	89 44 24 38          	mov    DWORD PTR [esp+0x38],eax
  4dd8fe:	8b cf                	mov    ecx,edi
  4dd900:	e8 3b 12 03 00       	call   0x50eb40
  4dd905:	03 d8                	add    ebx,eax
  4dd907:	8d 84 24 e0 17 00 00 	lea    eax,[esp+0x17e0]
  4dd90e:	50                   	push   eax
  4dd90f:	68 48 62 35 06       	push   0x6356248
  4dd914:	68 48 5e 35 06       	push   0x6355e48
  4dd919:	8d 84 24 54 18 00 00 	lea    eax,[esp+0x1854]
  4dd920:	68 7c 63 5a 00       	push   0x5a637c
  4dd925:	50                   	push   eax
  4dd926:	e8 a5 37 f2 ff       	call   0x4010d0
  4dd92b:	83 c4 24             	add    esp,0x24
  4dd92e:	8d 94 24 38 18 00 00 	lea    edx,[esp+0x1838]
  4dd935:	b9 01 00 00 00       	mov    ecx,0x1
  4dd93a:	e8 c1 49 08 00       	call   0x562300
  4dd93f:	33 c9                	xor    ecx,ecx
  4dd941:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  4dd945:	66 66 66 0f 1f 84 00 	data16 data16 nop WORD PTR [eax+eax*1+0x0]
  4dd94c:	00 00 00 00 
  4dd950:	8a 81 48 5a 35 06    	mov    al,BYTE PTR [ecx+0x6355a48]
  4dd956:	8d 49 01             	lea    ecx,[ecx+0x1]
  4dd959:	88 84 0c 37 20 00 00 	mov    BYTE PTR [esp+ecx*1+0x2037],al
  4dd960:	84 c0                	test   al,al
  4dd962:	75 ec                	jne    0x4dd950
  4dd964:	0f b6 84 24 38 20 00 	movzx  eax,BYTE PTR [esp+0x2038]
  4dd96b:	00 
  4dd96c:	50                   	push   eax
  4dd96d:	ff 15 04 c5 58 00    	call   DWORD PTR ds:0x58c504
  4dd973:	83 c4 04             	add    esp,0x4
  4dd976:	88 84 24 38 20 00 00 	mov    BYTE PTR [esp+0x2038],al
  4dd97d:	8d 84 24 38 20 00 00 	lea    eax,[esp+0x2038]
  4dd984:	50                   	push   eax
  4dd985:	8d 84 24 3c 18 00 00 	lea    eax,[esp+0x183c]
  4dd98c:	68 a0 63 5a 00       	push   0x5a63a0
  4dd991:	50                   	push   eax
  4dd992:	e8 39 37 f2 ff       	call   0x4010d0
  4dd997:	83 c4 0c             	add    esp,0xc
  4dd99a:	8d 94 24 38 18 00 00 	lea    edx,[esp+0x1838]
  4dd9a1:	33 c9                	xor    ecx,ecx
  4dd9a3:	e8 58 49 08 00       	call   0x562300
  4dd9a8:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4dd9af:	00 
  4dd9b0:	8b cf                	mov    ecx,edi
  4dd9b2:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4dd9b5:	6a 01                	push   0x1
  4dd9b7:	56                   	push   esi
  4dd9b8:	6a 64                	push   0x64
  4dd9ba:	ff 74 24 34          	push   DWORD PTR [esp+0x34]
  4dd9be:	f3 0f 59 05 80 d3 5d 	mulss  xmm0,DWORD PTR ds:0x5dd380
  4dd9c5:	00 
  4dd9c6:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4dd9ca:	03 d8                	add    ebx,eax
  4dd9cc:	8b d3                	mov    edx,ebx
  4dd9ce:	e8 6d 11 03 00       	call   0x50eb40
  4dd9d3:	f3 0f 10 0d 80 d3 5d 	movss  xmm1,DWORD PTR ds:0x5dd380
  4dd9da:	00 
  4dd9db:	83 c4 10             	add    esp,0x10
  4dd9de:	03 d8                	add    ebx,eax
  4dd9e0:	eb 04                	jmp    0x4dd9e6
  4dd9e2:	8b 74 24 3c          	mov    esi,DWORD PTR [esp+0x3c]
  4dd9e6:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4dd9ed:	00 
  4dd9ee:	8b cf                	mov    ecx,edi
  4dd9f0:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4dd9f3:	6a 01                	push   0x1
  4dd9f5:	56                   	push   esi
  4dd9f6:	f3 0f 59 c1          	mulss  xmm0,xmm1
  4dd9fa:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4dd9fe:	03 d8                	add    ebx,eax
  4dda00:	8d 84 24 40 24 00 00 	lea    eax,[esp+0x2440]
  4dda07:	50                   	push   eax
  4dda08:	8b d3                	mov    edx,ebx
  4dda0a:	e8 91 0b 03 00       	call   0x50e5a0
  4dda0f:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4dda16:	00 
  4dda17:	8d 84 24 44 28 00 00 	lea    eax,[esp+0x2844]
  4dda1e:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4dda21:	83 c4 0c             	add    esp,0xc
  4dda24:	8b cf                	mov    ecx,edi
  4dda26:	6a 01                	push   0x1
  4dda28:	f3 0f 2c d0          	cvttss2si edx,xmm0
  4dda2c:	56                   	push   esi
  4dda2d:	50                   	push   eax
  4dda2e:	03 d3                	add    edx,ebx
  4dda30:	e8 6b 0b 03 00       	call   0x50e5a0
  4dda35:	83 c4 0c             	add    esp,0xc
  4dda38:	8d 84 24 10 01 00 00 	lea    eax,[esp+0x110]
  4dda3f:	68 54 16 00 00       	push   0x1654
  4dda44:	50                   	push   eax
  4dda45:	68 e8 a6 72 0a       	push   0xa72a6e8
  4dda4a:	e8 51 db 0a 00       	call   0x58b5a0
  4dda4f:	83 c4 0c             	add    esp,0xc
  4dda52:	8b 8c 24 3c 30 00 00 	mov    ecx,DWORD PTR [esp+0x303c]
  4dda59:	5f                   	pop    edi
  4dda5a:	5e                   	pop    esi
  4dda5b:	5b                   	pop    ebx
  4dda5c:	33 cc                	xor    ecx,esp
  4dda5e:	e8 4b c6 0a 00       	call   0x58a0ae
  4dda63:	8b e5                	mov    esp,ebp
  4dda65:	5d                   	pop    ebp
  4dda66:	c3                   	ret
  4dda67:	cc                   	int3
  4dda68:	cc                   	int3
  4dda69:	cc                   	int3
  4dda6a:	cc                   	int3
  4dda6b:	cc                   	int3
  4dda6c:	cc                   	int3
  4dda6d:	cc                   	int3
  4dda6e:	cc                   	int3
  4dda6f:	cc                   	int3

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004de990 <.text+0xdd990>:
  4de990:	55                   	push   ebp
  4de991:	8b ec                	mov    ebp,esp
  4de993:	81 ec b4 05 00 00    	sub    esp,0x5b4
  4de999:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4de99e:	33 c5                	xor    eax,ebp
  4de9a0:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4de9a3:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4de9aa:	00 
  4de9ab:	83 c8 ff             	or     eax,0xffffffff
  4de9ae:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4de9b1:	53                   	push   ebx
  4de9b2:	56                   	push   esi
  4de9b3:	57                   	push   edi
  4de9b4:	8b f1                	mov    esi,ecx
  4de9b6:	89 85 54 fa ff ff    	mov    DWORD PTR [ebp-0x5ac],eax
  4de9bc:	33 db                	xor    ebx,ebx
  4de9be:	8d 48 02             	lea    ecx,[eax+0x2]
  4de9c1:	f3 0f 59 05 20 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd520
  4de9c8:	00 
  4de9c9:	89 9d 64 fa ff ff    	mov    DWORD PTR [ebp-0x59c],ebx
  4de9cf:	f3 0f 2c f8          	cvttss2si edi,xmm0
  4de9d3:	89 bd 50 fa ff ff    	mov    DWORD PTR [ebp-0x5b0],edi
  4de9d9:	e8 c2 ef 02 00       	call   0x50d9a0
  4de9de:	e8 0d d0 02 00       	call   0x50b9f0
  4de9e3:	8b 15 d4 10 61 0a    	mov    edx,DWORD PTR ds:0xa6110d4
  4de9e9:	51                   	push   ecx
  4de9ea:	68 58 02 00 00       	push   0x258
  4de9ef:	68 20 03 00 00       	push   0x320
  4de9f4:	83 ec 08             	sub    esp,0x8
  4de9f7:	33 c9                	xor    ecx,ecx
  4de9f9:	e8 c2 3d 03 00       	call   0x5127c0
  4de9fe:	83 c4 14             	add    esp,0x14
  4dea01:	ba 05 00 00 00       	mov    edx,0x5
  4dea06:	8b ca                	mov    ecx,edx
  4dea08:	6a 01                	push   0x1
  4dea0a:	68 78 65 5a 00       	push   0x5a6578
  4dea0f:	68 16 03 00 00       	push   0x316
  4dea14:	e8 97 6d 03 00       	call   0x5157b0
  4dea19:	83 c4 0c             	add    esp,0xc
  4dea1c:	e8 5f e9 ff ff       	call   0x4dd380
  4dea21:	83 fe ff             	cmp    esi,0xffffffff
  4dea24:	0f 84 5a 01 00 00    	je     0x4deb84
  4dea2a:	56                   	push   esi
  4dea2b:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4dea31:	68 bc 03 59 00       	push   0x5903bc
  4dea36:	50                   	push   eax
  4dea37:	e8 94 26 f2 ff       	call   0x4010d0
  4dea3c:	83 c4 0c             	add    esp,0xc
  4dea3f:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4dea45:	8b d7                	mov    edx,edi
  4dea47:	6a 01                	push   0x1
  4dea49:	50                   	push   eax
  4dea4a:	e8 b1 e9 ff ff       	call   0x4dd400
  4dea4f:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4dea54:	8b 35 f8 c1 58 00    	mov    esi,DWORD PTR ds:0x58c1f8
  4dea5a:	68 ff 00 00 00       	push   0xff
  4dea5f:	68 ff 00 00 00       	push   0xff
  4dea64:	68 ff 00 00 00       	push   0xff
  4dea69:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4dea6c:	ff d6                	call   esi
  4dea6e:	8b 15 a8 ac 35 06    	mov    edx,DWORD PTR ds:0x635aca8
  4dea74:	8d 4b 0a             	lea    ecx,[ebx+0xa]
  4dea77:	6a 01                	push   0x1
  4dea79:	50                   	push   eax
  4dea7a:	68 b0 65 5a 00       	push   0x5a65b0
  4dea7f:	8d 52 0a             	lea    edx,[edx+0xa]
  4dea82:	e8 19 fb 02 00       	call   0x50e5a0
  4dea87:	0f 10 05 c0 65 5a 00 	movups xmm0,XMMWORD PTR ds:0x5a65c0
  4dea8e:	a1 e8 65 5a 00       	mov    eax,ds:0x5a65e8
  4dea93:	8d 95 f8 fb ff ff    	lea    edx,[ebp-0x408]
  4dea99:	89 85 20 fc ff ff    	mov    DWORD PTR [ebp-0x3e0],eax
  4dea9f:	8d 4b 01             	lea    ecx,[ebx+0x1]
  4deaa2:	66 a1 ec 65 5a 00    	mov    ax,ds:0x5a65ec
  4deaa8:	83 c4 24             	add    esp,0x24
  4deaab:	0f 11 85 f8 fb ff ff 	movups XMMWORD PTR [ebp-0x408],xmm0
  4deab2:	66 89 85 24 fc ff ff 	mov    WORD PTR [ebp-0x3dc],ax
  4deab9:	0f 10 05 d0 65 5a 00 	movups xmm0,XMMWORD PTR ds:0x5a65d0
  4deac0:	a0 ee 65 5a 00       	mov    al,ds:0x5a65ee
  4deac5:	88 85 26 fc ff ff    	mov    BYTE PTR [ebp-0x3da],al
  4deacb:	0f 11 85 08 fc ff ff 	movups XMMWORD PTR [ebp-0x3f8],xmm0
  4dead2:	f3 0f 7e 05 e0 65 5a 	movq   xmm0,QWORD PTR ds:0x5a65e0
  4dead9:	00 
  4deada:	66 0f d6 85 18 fc ff 	movq   QWORD PTR [ebp-0x3e8],xmm0
  4deae1:	ff 
  4deae2:	e8 19 38 08 00       	call   0x562300
  4deae7:	ba f0 65 5a 00       	mov    edx,0x5a65f0
  4deaec:	33 c9                	xor    ecx,ecx
  4deaee:	e8 0d 38 08 00       	call   0x562300
  4deaf3:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4deaf8:	6a 54                	push   0x54
  4deafa:	68 fc 00 00 00       	push   0xfc
  4deaff:	68 fc 00 00 00       	push   0xfc
  4deb04:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4deb07:	ff d6                	call   esi
  4deb09:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4deb10:	00 
  4deb11:	8d 4b 0a             	lea    ecx,[ebx+0xa]
  4deb14:	8b 15 a8 ac 35 06    	mov    edx,DWORD PTR ds:0x635aca8
  4deb1a:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4deb1d:	6a 01                	push   0x1
  4deb1f:	50                   	push   eax
  4deb20:	a1 ac ac 35 06       	mov    eax,ds:0x635acac
  4deb25:	83 c0 ec             	add    eax,0xffffffec
  4deb28:	ff 35 b0 ac 35 06    	push   DWORD PTR ds:0x635acb0
  4deb2e:	f3 0f 59 05 20 d7 5d 	mulss  xmm0,DWORD PTR ds:0x5dd720
  4deb35:	00 
  4deb36:	50                   	push   eax
  4deb37:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4deb3b:	2b d0                	sub    edx,eax
  4deb3d:	83 c2 0a             	add    edx,0xa
  4deb40:	e8 fb ff 02 00       	call   0x50eb40
  4deb45:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4deb4c:	00 
  4deb4d:	8d 4b 0a             	lea    ecx,[ebx+0xa]
  4deb50:	8b 15 b0 ac 35 06    	mov    edx,DWORD PTR ds:0x635acb0
  4deb56:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4deb59:	68 70 50 59 00       	push   0x595070
  4deb5e:	f3 0f 59 05 98 d4 5d 	mulss  xmm0,DWORD PTR ds:0x5dd498
  4deb65:	00 
  4deb66:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4deb6a:	2b d0                	sub    edx,eax
  4deb6c:	03 15 a8 ac 35 06    	add    edx,DWORD PTR ds:0x635aca8
  4deb72:	e8 09 5b 03 00       	call   0x514680
  4deb77:	83 c4 24             	add    esp,0x24
  4deb7a:	e8 01 51 ff ff       	call   0x4d3c80
  4deb7f:	e9 c3 08 00 00       	jmp    0x4df447
  4deb84:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4deb8b:	00 
  4deb8c:	b8 58 02 00 00       	mov    eax,0x258
  4deb91:	2b 05 b0 ac 35 06    	sub    eax,DWORD PTR ds:0x635acb0
  4deb97:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4deb9a:	2b c7                	sub    eax,edi
  4deb9c:	99                   	cdq
  4deb9d:	f3 0f 59 05 3c d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd53c
  4deba4:	00 
  4deba5:	f3 0f 2c c8          	cvttss2si ecx,xmm0
  4deba9:	f7 f9                	idiv   ecx
  4debab:	89 8d 4c fa ff ff    	mov    DWORD PTR [ebp-0x5b4],ecx
  4debb1:	33 d2                	xor    edx,edx
  4debb3:	b9 48 66 5a 00       	mov    ecx,0x5a6648
  4debb8:	89 85 5c fa ff ff    	mov    DWORD PTR [ebp-0x5a4],eax
  4debbe:	e8 7d d9 02 00       	call   0x50c540
  4debc3:	e8 a8 ee ff ff       	call   0x4dda70
  4debc8:	8b 15 a0 ac 35 06    	mov    edx,DWORD PTR ds:0x635aca0
  4debce:	33 ff                	xor    edi,edi
  4debd0:	8b ca                	mov    ecx,edx
  4debd2:	89 bd 60 fa ff ff    	mov    DWORD PTR [ebp-0x5a0],edi
  4debd8:	85 c9                	test   ecx,ecx
  4debda:	78 1f                	js     0x4debfb
  4debdc:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  4debe0:	38 99 34 ae 35 06    	cmp    BYTE PTR [ecx+0x635ae34],bl
  4debe6:	74 08                	je     0x4debf0
  4debe8:	89 8c bd 30 fb ff ff 	mov    DWORD PTR [ebp+edi*4-0x4d0],ecx
  4debef:	47                   	inc    edi
  4debf0:	83 e9 01             	sub    ecx,0x1
  4debf3:	79 eb                	jns    0x4debe0
  4debf5:	89 bd 60 fa ff ff    	mov    DWORD PTR [ebp-0x5a0],edi
  4debfb:	b8 31 00 00 00       	mov    eax,0x31
  4dec00:	3b d0                	cmp    edx,eax
  4dec02:	73 1b                	jae    0x4dec1f
  4dec04:	38 98 34 ae 35 06    	cmp    BYTE PTR [eax+0x635ae34],bl
  4dec0a:	74 08                	je     0x4dec14
  4dec0c:	89 84 bd 30 fb ff ff 	mov    DWORD PTR [ebp+edi*4-0x4d0],eax
  4dec13:	47                   	inc    edi
  4dec14:	48                   	dec    eax
  4dec15:	3b c2                	cmp    eax,edx
  4dec17:	77 eb                	ja     0x4dec04
  4dec19:	89 bd 60 fa ff ff    	mov    DWORD PTR [ebp-0x5a0],edi
  4dec1f:	85 ff                	test   edi,edi
  4dec21:	74 10                	je     0x4dec33
  4dec23:	8b cf                	mov    ecx,edi
  4dec25:	8d b5 30 fb ff ff    	lea    esi,[ebp-0x4d0]
  4dec2b:	8d bd 68 fa ff ff    	lea    edi,[ebp-0x598]
  4dec31:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  4dec33:	8b 35 f8 c1 58 00    	mov    esi,DWORD PTR ds:0x58c1f8
  4dec39:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  4dec40:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4dec45:	6a 64                	push   0x64
  4dec47:	68 58 02 00 00       	push   0x258
  4dec4c:	68 20 03 00 00       	push   0x320
  4dec51:	6a 00                	push   0x0
  4dec53:	6a 00                	push   0x0
  4dec55:	6a 54                	push   0x54
  4dec57:	68 fc 00 00 00       	push   0xfc
  4dec5c:	68 fc 00 00 00       	push   0xfc
  4dec61:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4dec64:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4dec6b:	00 00 00 
  4dec6e:	ff d6                	call   esi
  4dec70:	83 c4 10             	add    esp,0x10
  4dec73:	ba 16 c6 58 00       	mov    edx,0x58c616
  4dec78:	8b c8                	mov    ecx,eax
  4dec7a:	e8 11 0b ff ff       	call   0x4cf790
  4dec7f:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4dec84:	83 c4 14             	add    esp,0x14
  4dec87:	68 ff 00 00 00       	push   0xff
  4dec8c:	68 ff 00 00 00       	push   0xff
  4dec91:	68 ff 00 00 00       	push   0xff
  4dec96:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4dec99:	ff d6                	call   esi
  4dec9b:	8b 0d 8c 4b 35 06    	mov    ecx,DWORD PTR ds:0x6354b8c
  4deca1:	83 c4 10             	add    esp,0x10
  4deca4:	85 c0                	test   eax,eax
  4deca6:	c7 05 a8 4a 35 06 00 	mov    DWORD PTR ds:0x6354aa8,0x0
  4decad:	00 00 00 
  4decb0:	0f 49 c8             	cmovns ecx,eax
  4decb3:	83 f8 fe             	cmp    eax,0xfffffffe
  4decb6:	89 0d 8c 4b 35 06    	mov    DWORD PTR ds:0x6354b8c,ecx
  4decbc:	b8 01 00 00 00       	mov    eax,0x1
  4decc1:	8b 0d 9c 4a 35 06    	mov    ecx,DWORD PTR ds:0x6354a9c
  4decc7:	0f 44 c8             	cmove  ecx,eax
  4decca:	89 0d 9c 4a 35 06    	mov    DWORD PTR ds:0x6354a9c,ecx
  4decd0:	33 c9                	xor    ecx,ecx
  4decd2:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  4decd6:	66 66 0f 1f 84 00 00 	data16 nop WORD PTR [eax+eax*1+0x0]
  4decdd:	00 00 00 
  4dece0:	8a 81 16 c6 58 00    	mov    al,BYTE PTR [ecx+0x58c616]
  4dece6:	8d 49 01             	lea    ecx,[ecx+0x1]
  4dece9:	88 81 c3 4a 35 06    	mov    BYTE PTR [ecx+0x6354ac3],al
  4decef:	84 c0                	test   al,al
  4decf1:	75 ed                	jne    0x4dece0
  4decf3:	33 c9                	xor    ecx,ecx
  4decf5:	66 66 66 0f 1f 84 00 	data16 data16 nop WORD PTR [eax+eax*1+0x0]
  4decfc:	00 00 00 00 
  4ded00:	8a 81 16 c6 58 00    	mov    al,BYTE PTR [ecx+0x58c616]
  4ded06:	8d 49 01             	lea    ecx,[ecx+0x1]
  4ded09:	88 81 27 4b 35 06    	mov    BYTE PTR [ecx+0x6354b27],al
  4ded0f:	84 c0                	test   al,al
  4ded11:	75 ed                	jne    0x4ded00
  4ded13:	c7 05 b4 4a 35 06 01 	mov    DWORD PTR ds:0x6354ab4,0x1
  4ded1a:	00 00 00 
  4ded1d:	e8 8e 12 ff ff       	call   0x4cffb0
  4ded22:	b9 58 63 5a 00       	mov    ecx,0x5a6358
  4ded27:	c7 05 9c 4a 35 06 01 	mov    DWORD PTR ds:0x6354a9c,0x1
  4ded2e:	00 00 00 
  4ded31:	c7 05 a0 4a 35 06 01 	mov    DWORD PTR ds:0x6354aa0,0x1
  4ded38:	00 00 00 
  4ded3b:	e8 10 c5 02 00       	call   0x50b250
  4ded40:	8b 3d 34 4a 35 06    	mov    edi,DWORD PTR ds:0x6354a34
  4ded46:	33 f6                	xor    esi,esi
  4ded48:	39 b5 5c fa ff ff    	cmp    DWORD PTR [ebp-0x5a4],esi
  4ded4e:	0f 8e 13 01 00 00    	jle    0x4dee67
  4ded54:	8b 85 64 fa ff ff    	mov    eax,DWORD PTR [ebp-0x59c]
  4ded5a:	8d 8d 30 fb ff ff    	lea    ecx,[ebp-0x4d0]
  4ded60:	8b 9d 50 fa ff ff    	mov    ebx,DWORD PTR [ebp-0x5b0]
  4ded66:	8b 95 60 fa ff ff    	mov    edx,DWORD PTR [ebp-0x5a0]
  4ded6c:	8d 0c 81             	lea    ecx,[ecx+eax*4]
  4ded6f:	89 8d 58 fa ff ff    	mov    DWORD PTR [ebp-0x5a8],ecx
  4ded75:	03 c6                	add    eax,esi
  4ded77:	3b c2                	cmp    eax,edx
  4ded79:	0f 83 c4 00 00 00    	jae    0x4dee43
  4ded7f:	ff 31                	push   DWORD PTR [ecx]
  4ded81:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4ded87:	68 bc 03 59 00       	push   0x5903bc
  4ded8c:	50                   	push   eax
  4ded8d:	e8 3e 23 f2 ff       	call   0x4010d0
  4ded92:	83 c4 0c             	add    esp,0xc
  4ded95:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4ded9b:	8b d3                	mov    edx,ebx
  4ded9d:	6a 00                	push   0x0
  4ded9f:	50                   	push   eax
  4deda0:	e8 5b e6 ff ff       	call   0x4dd400
  4deda5:	8b 3d 34 4a 35 06    	mov    edi,DWORD PTR ds:0x6354a34
  4dedab:	8d 43 fb             	lea    eax,[ebx-0x5]
  4dedae:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4dedb5:	00 
  4dedb6:	b9 0a 00 00 00       	mov    ecx,0xa
  4dedbb:	69 d7 e8 00 00 00    	imul   edx,edi,0xe8
  4dedc1:	83 c4 08             	add    esp,0x8
  4dedc4:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4dedc7:	f3 0f 59 05 44 d7 5d 	mulss  xmm0,DWORD PTR ds:0x5dd744
  4dedce:	00 
  4dedcf:	c7 82 e0 ef 34 06 05 	mov    DWORD PTR [edx+0x634efe0],0x5
  4dedd6:	00 00 00 
  4dedd9:	89 82 e4 ef 34 06    	mov    DWORD PTR [edx+0x634efe4],eax
  4deddf:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4dede3:	0f 10 05 c0 4d 5a 00 	movups xmm0,XMMWORD PTR ds:0x5a4dc0
  4dedea:	2b c8                	sub    ecx,eax
  4dedec:	a0 f0 4d 5a 00       	mov    al,ds:0x5a4df0
  4dedf1:	89 8a e8 ef 34 06    	mov    DWORD PTR [edx+0x634efe8],ecx
  4dedf7:	47                   	inc    edi
  4dedf8:	89 8a ec ef 34 06    	mov    DWORD PTR [edx+0x634efec],ecx
  4dedfe:	8b 8d 58 fa ff ff    	mov    ecx,DWORD PTR [ebp-0x5a8]
  4dee04:	c7 82 d8 ef 34 06 00 	mov    DWORD PTR [edx+0x634efd8],0x0
  4dee0b:	00 00 00 
  4dee0e:	0f 11 82 10 ef 34 06 	movups XMMWORD PTR [edx+0x634ef10],xmm0
  4dee15:	89 3d 34 4a 35 06    	mov    DWORD PTR ds:0x6354a34,edi
  4dee1b:	0f 10 05 d0 4d 5a 00 	movups xmm0,XMMWORD PTR ds:0x5a4dd0
  4dee22:	0f 11 82 20 ef 34 06 	movups XMMWORD PTR [edx+0x634ef20],xmm0
  4dee29:	0f 10 05 e0 4d 5a 00 	movups xmm0,XMMWORD PTR ds:0x5a4de0
  4dee30:	0f 11 82 30 ef 34 06 	movups XMMWORD PTR [edx+0x634ef30],xmm0
  4dee37:	88 82 40 ef 34 06    	mov    BYTE PTR [edx+0x634ef40],al
  4dee3d:	8b 95 60 fa ff ff    	mov    edx,DWORD PTR [ebp-0x5a0]
  4dee43:	03 9d 4c fa ff ff    	add    ebx,DWORD PTR [ebp-0x5b4]
  4dee49:	46                   	inc    esi
  4dee4a:	8b 85 64 fa ff ff    	mov    eax,DWORD PTR [ebp-0x59c]
  4dee50:	83 c1 04             	add    ecx,0x4
  4dee53:	89 8d 58 fa ff ff    	mov    DWORD PTR [ebp-0x5a8],ecx
  4dee59:	3b b5 5c fa ff ff    	cmp    esi,DWORD PTR [ebp-0x5a4]
  4dee5f:	0f 8c 10 ff ff ff    	jl     0x4ded75
  4dee65:	8b d8                	mov    ebx,eax
  4dee67:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4dee6c:	89 3d bc 4a 35 06    	mov    DWORD PTR ds:0x6354abc,edi
  4dee72:	8b bd 60 fa ff ff    	mov    edi,DWORD PTR [ebp-0x5a0]
  4dee78:	85 ff                	test   edi,edi
  4dee7a:	74 3b                	je     0x4deeb7
  4dee7c:	68 ff 00 00 00       	push   0xff
  4dee81:	68 ff 00 00 00       	push   0xff
  4dee86:	68 ff 00 00 00       	push   0xff
  4dee8b:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4dee8e:	a1 f8 c1 58 00       	mov    eax,ds:0x58c1f8
  4dee93:	ff d0                	call   eax
  4dee95:	8b 15 a8 ac 35 06    	mov    edx,DWORD PTR ds:0x635aca8
  4dee9b:	83 c4 0c             	add    esp,0xc
  4dee9e:	8b 0d a4 ac 35 06    	mov    ecx,DWORD PTR ds:0x635aca4
  4deea4:	50                   	push   eax
  4deea5:	68 50 66 5a 00       	push   0x5a6650
  4deeaa:	8d 52 0a             	lea    edx,[edx+0xa]
  4deead:	8d 49 0a             	lea    ecx,[ecx+0xa]
  4deeb0:	e8 6b f8 02 00       	call   0x50e720
  4deeb5:	eb 34                	jmp    0x4deeeb
  4deeb7:	6a 01                	push   0x1
  4deeb9:	68 ff 00 00 00       	push   0xff
  4deebe:	68 ff 00 00 00       	push   0xff
  4deec3:	68 ff 00 00 00       	push   0xff
  4deec8:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4deecb:	a1 f8 c1 58 00       	mov    eax,ds:0x58c1f8
  4deed0:	ff d0                	call   eax
  4deed2:	8b 95 50 fa ff ff    	mov    edx,DWORD PTR [ebp-0x5b0]
  4deed8:	83 c4 10             	add    esp,0x10
  4deedb:	b9 0a 00 00 00       	mov    ecx,0xa
  4deee0:	50                   	push   eax
  4deee1:	68 ac 66 5a 00       	push   0x5a66ac
  4deee6:	e8 b5 f6 02 00       	call   0x50e5a0
  4deeeb:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4deef2:	00 
  4deef3:	83 c4 0c             	add    esp,0xc
  4deef6:	8b 15 a4 ac 35 06    	mov    edx,DWORD PTR ds:0x635aca4
  4deefc:	b9 1b 00 00 00       	mov    ecx,0x1b
  4def01:	8b 35 a8 ac 35 06    	mov    esi,DWORD PTR ds:0x635aca8
  4def07:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4def0a:	68 c8 50 59 00       	push   0x5950c8
  4def0f:	8d 52 0a             	lea    edx,[edx+0xa]
  4def12:	f3 0f 59 05 38 d7 5d 	mulss  xmm0,DWORD PTR ds:0x5dd738
  4def19:	00 
  4def1a:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4def1e:	2b f0                	sub    esi,eax
  4def20:	56                   	push   esi
  4def21:	e8 ca 0b ff ff       	call   0x4cfaf0
  4def26:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4def2b:	68 ab 00 00 00       	push   0xab
  4def30:	68 ab 00 00 00       	push   0xab
  4def35:	68 ab 00 00 00       	push   0xab
  4def3a:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4def3d:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4def43:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4def4a:	00 
  4def4b:	8b d6                	mov    edx,esi
  4def4d:	8b 0d a4 ac 35 06    	mov    ecx,DWORD PTR ds:0x635aca4
  4def53:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4def56:	6a 01                	push   0x1
  4def58:	50                   	push   eax
  4def59:	68 d0 66 5a 00       	push   0x5a66d0
  4def5e:	8d 89 6a 01 00 00    	lea    ecx,[ecx+0x16a]
  4def64:	f3 0f 59 05 d8 d6 5d 	mulss  xmm0,DWORD PTR ds:0x5dd6d8
  4def6b:	00 
  4def6c:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4def70:	2b d0                	sub    edx,eax
  4def72:	e8 29 f6 02 00       	call   0x50e5a0
  4def77:	8b 15 a4 ac 35 06    	mov    edx,DWORD PTR ds:0x635aca4
  4def7d:	83 c4 24             	add    esp,0x24
  4def80:	b9 50 00 00 00       	mov    ecx,0x50
  4def85:	68 dc 66 5a 00       	push   0x5a66dc
  4def8a:	56                   	push   esi
  4def8b:	8d 92 c2 01 00 00    	lea    edx,[edx+0x1c2]
  4def91:	e8 5a 0b ff ff       	call   0x4cfaf0
  4def96:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4def9d:	00 
  4def9e:	8b ce                	mov    ecx,esi
  4defa0:	8b 15 a4 ac 35 06    	mov    edx,DWORD PTR ds:0x635aca4
  4defa6:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4defa9:	68 00 67 5a 00       	push   0x5a6700
  4defae:	8d 92 c2 01 00 00    	lea    edx,[edx+0x1c2]
  4defb4:	f3 0f 59 05 00 d7 5d 	mulss  xmm0,DWORD PTR ds:0x5dd700
  4defbb:	00 
  4defbc:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4defc0:	2b c8                	sub    ecx,eax
  4defc2:	51                   	push   ecx
  4defc3:	b9 4c 00 00 00       	mov    ecx,0x4c
  4defc8:	e8 23 0b ff ff       	call   0x4cfaf0
  4defcd:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4defd4:	00 
  4defd5:	8b ce                	mov    ecx,esi
  4defd7:	8b 15 a4 ac 35 06    	mov    edx,DWORD PTR ds:0x635aca4
  4defdd:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4defe0:	68 14 67 5a 00       	push   0x5a6714
  4defe5:	8d 92 c2 01 00 00    	lea    edx,[edx+0x1c2]
  4defeb:	f3 0f 59 05 38 d7 5d 	mulss  xmm0,DWORD PTR ds:0x5dd738
  4deff2:	00 
  4deff3:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4deff7:	2b c8                	sub    ecx,eax
  4deff9:	51                   	push   ecx
  4deffa:	b9 4a 00 00 00       	mov    ecx,0x4a
  4defff:	e8 ec 0a ff ff       	call   0x4cfaf0
  4df004:	83 c4 18             	add    esp,0x18
  4df007:	85 db                	test   ebx,ebx
  4df009:	74 37                	je     0x4df042
  4df00b:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4df012:	00 
  4df013:	8b ce                	mov    ecx,esi
  4df015:	8b 15 a4 ac 35 06    	mov    edx,DWORD PTR ds:0x635aca4
  4df01b:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4df01e:	68 2c 67 5a 00       	push   0x5a672c
  4df023:	8d 52 0a             	lea    edx,[edx+0xa]
  4df026:	f3 0f 59 05 00 d7 5d 	mulss  xmm0,DWORD PTR ds:0x5dd700
  4df02d:	00 
  4df02e:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4df032:	2b c8                	sub    ecx,eax
  4df034:	51                   	push   ecx
  4df035:	b9 31 04 00 00       	mov    ecx,0x431
  4df03a:	e8 b1 0a ff ff       	call   0x4cfaf0
  4df03f:	83 c4 08             	add    esp,0x8
  4df042:	8b 85 5c fa ff ff    	mov    eax,DWORD PTR [ebp-0x5a4]
  4df048:	03 c3                	add    eax,ebx
  4df04a:	89 85 58 fa ff ff    	mov    DWORD PTR [ebp-0x5a8],eax
  4df050:	3b c7                	cmp    eax,edi
  4df052:	73 35                	jae    0x4df089
  4df054:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4df05b:	00 
  4df05c:	b9 39 04 00 00       	mov    ecx,0x439
  4df061:	8b 15 a4 ac 35 06    	mov    edx,DWORD PTR ds:0x635aca4
  4df067:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4df06a:	68 b8 5c 59 00       	push   0x595cb8
  4df06f:	8d 52 0a             	lea    edx,[edx+0xa]
  4df072:	f3 0f 59 05 38 d7 5d 	mulss  xmm0,DWORD PTR ds:0x5dd738
  4df079:	00 
  4df07a:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4df07e:	2b f0                	sub    esi,eax
  4df080:	56                   	push   esi
  4df081:	e8 6a 0a ff ff       	call   0x4cfaf0
  4df086:	83 c4 08             	add    esp,0x8
  4df089:	8b b5 5c fa ff ff    	mov    esi,DWORD PTR [ebp-0x5a4]
  4df08f:	3b fe                	cmp    edi,esi
  4df091:	0f 86 86 00 00 00    	jbe    0x4df11d
  4df097:	33 d2                	xor    edx,edx
  4df099:	8b c7                	mov    eax,edi
  4df09b:	f7 f6                	div    esi
  4df09d:	8b c8                	mov    ecx,eax
  4df09f:	0f af ce             	imul   ecx,esi
  4df0a2:	3b cf                	cmp    ecx,edi
  4df0a4:	73 01                	jae    0x4df0a7
  4df0a6:	40                   	inc    eax
  4df0a7:	50                   	push   eax
  4df0a8:	8b c3                	mov    eax,ebx
  4df0aa:	99                   	cdq
  4df0ab:	f7 fe                	idiv   esi
  4df0ad:	40                   	inc    eax
  4df0ae:	50                   	push   eax
  4df0af:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4df0b5:	68 40 67 5a 00       	push   0x5a6740
  4df0ba:	50                   	push   eax
  4df0bb:	e8 10 20 f2 ff       	call   0x4010d0
  4df0c0:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4df0c5:	68 ab 00 00 00       	push   0xab
  4df0ca:	68 ab 00 00 00       	push   0xab
  4df0cf:	68 ab 00 00 00       	push   0xab
  4df0d4:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4df0d7:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4df0dd:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4df0e4:	00 
  4df0e5:	8b 0d a4 ac 35 06    	mov    ecx,DWORD PTR ds:0x635aca4
  4df0eb:	8b 15 b0 ac 35 06    	mov    edx,DWORD PTR ds:0x635acb0
  4df0f1:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4df0f4:	6a 01                	push   0x1
  4df0f6:	50                   	push   eax
  4df0f7:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4df0fd:	50                   	push   eax
  4df0fe:	8d 49 0a             	lea    ecx,[ecx+0xa]
  4df101:	f3 0f 59 05 38 d2 5d 	mulss  xmm0,DWORD PTR ds:0x5dd238
  4df108:	00 
  4df109:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4df10d:	2b d0                	sub    edx,eax
  4df10f:	03 15 a8 ac 35 06    	add    edx,DWORD PTR ds:0x635aca8
  4df115:	e8 86 f4 02 00       	call   0x50e5a0
  4df11a:	83 c4 2c             	add    esp,0x2c
  4df11d:	c7 05 5c ba 5b 06 00 	mov    DWORD PTR ds:0x65bba5c,0x0
  4df124:	00 00 00 
  4df127:	e8 64 be 02 00       	call   0x50af90
  4df12c:	83 3d d8 bc 5b 06 00 	cmp    DWORD PTR ds:0x65bbcd8,0x0
  4df133:	74 17                	je     0x4df14c
  4df135:	e8 06 0f 03 00       	call   0x510040
  4df13a:	a1 d8 bc 5b 06       	mov    eax,ds:0x65bbcd8
  4df13f:	33 c9                	xor    ecx,ecx
  4df141:	83 f8 02             	cmp    eax,0x2
  4df144:	0f 44 c1             	cmove  eax,ecx
  4df147:	a3 d8 bc 5b 06       	mov    ds:0x65bbcd8,eax
  4df14c:	e8 6f c2 02 00       	call   0x50b3c0
  4df151:	83 3d 54 1c 5c 0a 00 	cmp    DWORD PTR ds:0xa5c1c54,0x0
  4df158:	75 0f                	jne    0x4df169
  4df15a:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4df160:	ff 15 7c c2 58 00    	call   DWORD PTR ds:0x58c27c
  4df166:	83 c4 04             	add    esp,0x4
  4df169:	8b 85 54 fa ff ff    	mov    eax,DWORD PTR [ebp-0x5ac]
  4df16f:	83 f8 ff             	cmp    eax,0xffffffff
  4df172:	74 0e                	je     0x4df182
  4df174:	a3 b0 4a 35 06       	mov    ds:0x6354ab0,eax
  4df179:	83 c8 ff             	or     eax,0xffffffff
  4df17c:	89 85 54 fa ff ff    	mov    DWORD PTR [ebp-0x5ac],eax
  4df182:	e8 99 1f ff ff       	call   0x4d1120
  4df187:	8b d0                	mov    edx,eax
  4df189:	83 fa ff             	cmp    edx,0xffffffff
  4df18c:	74 f4                	je     0x4df182
  4df18e:	83 fa 64             	cmp    edx,0x64
  4df191:	7c 04                	jl     0x4df197
  4df193:	33 c9                	xor    ecx,ecx
  4df195:	eb 23                	jmp    0x4df1ba
  4df197:	85 d2                	test   edx,edx
  4df199:	79 04                	jns    0x4df19f
  4df19b:	33 c9                	xor    ecx,ecx
  4df19d:	eb 1b                	jmp    0x4df1ba
  4df19f:	69 c2 e8 00 00 00    	imul   eax,edx,0xe8
  4df1a5:	8b 88 d8 ef 34 06    	mov    ecx,DWORD PTR [eax+0x634efd8]
  4df1ab:	83 f9 50             	cmp    ecx,0x50
  4df1ae:	0f 8f 63 01 00 00    	jg     0x4df317
  4df1b4:	0f 84 f8 00 00 00    	je     0x4df2b2
  4df1ba:	83 e9 1b             	sub    ecx,0x1b
  4df1bd:	0f 84 7a 02 00 00    	je     0x4df43d
  4df1c3:	83 e9 2f             	sub    ecx,0x2f
  4df1c6:	74 7c                	je     0x4df244
  4df1c8:	83 e9 02             	sub    ecx,0x2
  4df1cb:	0f 85 57 01 00 00    	jne    0x4df328
  4df1d1:	b9 48 66 5a 00       	mov    ecx,0x5a6648
  4df1d6:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4df1dd:	00 00 00 
  4df1e0:	e8 ab d4 02 00       	call   0x50c690
  4df1e5:	4f                   	dec    edi
  4df1e6:	85 ff                	test   edi,edi
  4df1e8:	7e 4d                	jle    0x4df237
  4df1ea:	8b df                	mov    ebx,edi
  4df1ec:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  4df1f0:	33 c9                	xor    ecx,ecx
  4df1f2:	85 ff                	test   edi,edi
  4df1f4:	7e 3b                	jle    0x4df231
  4df1f6:	66 66 0f 1f 84 00 00 	data16 nop WORD PTR [eax+eax*1+0x0]
  4df1fd:	00 00 00 
  4df200:	8b b4 8d 30 fb ff ff 	mov    esi,DWORD PTR [ebp+ecx*4-0x4d0]
  4df207:	8b 94 8d 34 fb ff ff 	mov    edx,DWORD PTR [ebp+ecx*4-0x4cc]
  4df20e:	8b 04 b5 98 b3 35 06 	mov    eax,DWORD PTR [esi*4+0x635b398]
  4df215:	3b 04 95 98 b3 35 06 	cmp    eax,DWORD PTR [edx*4+0x635b398]
  4df21c:	73 0e                	jae    0x4df22c
  4df21e:	89 94 8d 30 fb ff ff 	mov    DWORD PTR [ebp+ecx*4-0x4d0],edx
  4df225:	89 b4 8d 34 fb ff ff 	mov    DWORD PTR [ebp+ecx*4-0x4cc],esi
  4df22c:	41                   	inc    ecx
  4df22d:	3b cf                	cmp    ecx,edi
  4df22f:	7c cf                	jl     0x4df200
  4df231:	4f                   	dec    edi
  4df232:	83 eb 01             	sub    ebx,0x1
  4df235:	75 b9                	jne    0x4df1f0
  4df237:	33 db                	xor    ebx,ebx
  4df239:	89 9d 64 fa ff ff    	mov    DWORD PTR [ebp-0x59c],ebx
  4df23f:	e9 ef f9 ff ff       	jmp    0x4dec33
  4df244:	b9 48 66 5a 00       	mov    ecx,0x5a6648
  4df249:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4df250:	00 00 00 
  4df253:	e8 38 d4 02 00       	call   0x50c690
  4df258:	4f                   	dec    edi
  4df259:	85 ff                	test   edi,edi
  4df25b:	7e da                	jle    0x4df237
  4df25d:	8b df                	mov    ebx,edi
  4df25f:	90                   	nop
  4df260:	33 c9                	xor    ecx,ecx
  4df262:	85 ff                	test   edi,edi
  4df264:	7e 3b                	jle    0x4df2a1
  4df266:	66 66 0f 1f 84 00 00 	data16 nop WORD PTR [eax+eax*1+0x0]
  4df26d:	00 00 00 
  4df270:	8b b4 8d 30 fb ff ff 	mov    esi,DWORD PTR [ebp+ecx*4-0x4d0]
  4df277:	8b 94 8d 34 fb ff ff 	mov    edx,DWORD PTR [ebp+ecx*4-0x4cc]
  4df27e:	8b 04 b5 68 ae 35 06 	mov    eax,DWORD PTR [esi*4+0x635ae68]
  4df285:	3b 04 95 68 ae 35 06 	cmp    eax,DWORD PTR [edx*4+0x635ae68]
  4df28c:	73 0e                	jae    0x4df29c
  4df28e:	89 94 8d 30 fb ff ff 	mov    DWORD PTR [ebp+ecx*4-0x4d0],edx
  4df295:	89 b4 8d 34 fb ff ff 	mov    DWORD PTR [ebp+ecx*4-0x4cc],esi
  4df29c:	41                   	inc    ecx
  4df29d:	3b cf                	cmp    ecx,edi
  4df29f:	7c cf                	jl     0x4df270
  4df2a1:	4f                   	dec    edi
  4df2a2:	83 eb 01             	sub    ebx,0x1
  4df2a5:	75 b9                	jne    0x4df260
  4df2a7:	89 9d 64 fa ff ff    	mov    DWORD PTR [ebp-0x59c],ebx
  4df2ad:	e9 81 f9 ff ff       	jmp    0x4dec33
  4df2b2:	b9 48 66 5a 00       	mov    ecx,0x5a6648
  4df2b7:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4df2be:	00 00 00 
  4df2c1:	e8 ca d3 02 00       	call   0x50c690
  4df2c6:	85 ff                	test   edi,edi
  4df2c8:	74 16                	je     0x4df2e0
  4df2ca:	8b cf                	mov    ecx,edi
  4df2cc:	8d b5 68 fa ff ff    	lea    esi,[ebp-0x598]
  4df2d2:	8d bd 30 fb ff ff    	lea    edi,[ebp-0x4d0]
  4df2d8:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  4df2da:	8b b5 5c fa ff ff    	mov    esi,DWORD PTR [ebp-0x5a4]
  4df2e0:	33 db                	xor    ebx,ebx
  4df2e2:	b9 48 66 5a 00       	mov    ecx,0x5a6648
  4df2e7:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4df2ee:	00 00 00 
  4df2f1:	e8 9a d3 02 00       	call   0x50c690
  4df2f6:	2b de                	sub    ebx,esi
  4df2f8:	8b 35 f8 c1 58 00    	mov    esi,DWORD PTR ds:0x58c1f8
  4df2fe:	89 9d 64 fa ff ff    	mov    DWORD PTR [ebp-0x59c],ebx
  4df304:	0f 89 36 f9 ff ff    	jns    0x4dec40
  4df30a:	33 db                	xor    ebx,ebx
  4df30c:	89 9d 64 fa ff ff    	mov    DWORD PTR [ebp-0x59c],ebx
  4df312:	e9 1c f9 ff ff       	jmp    0x4dec33
  4df317:	81 e9 31 04 00 00    	sub    ecx,0x431
  4df31d:	74 c3                	je     0x4df2e2
  4df31f:	83 e9 08             	sub    ecx,0x8
  4df322:	0f 84 f0 00 00 00    	je     0x4df418
  4df328:	8d 04 13             	lea    eax,[ebx+edx*1]
  4df32b:	89 95 54 fa ff ff    	mov    DWORD PTR [ebp-0x5ac],edx
  4df331:	ff b4 85 30 fb ff ff 	push   DWORD PTR [ebp+eax*4-0x4d0]
  4df338:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4df33e:	68 bc 03 59 00       	push   0x5903bc
  4df343:	50                   	push   eax
  4df344:	e8 87 1d f2 ff       	call   0x4010d0
  4df349:	83 c4 0c             	add    esp,0xc
  4df34c:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4df353:	00 00 00 
  4df356:	b9 48 66 5a 00       	mov    ecx,0x5a6648
  4df35b:	e8 30 d3 02 00       	call   0x50c690
  4df360:	8b 95 50 fa ff ff    	mov    edx,DWORD PTR [ebp-0x5b0]
  4df366:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4df36c:	6a 01                	push   0x1
  4df36e:	50                   	push   eax
  4df36f:	e8 8c e0 ff ff       	call   0x4dd400
  4df374:	83 c4 08             	add    esp,0x8
  4df377:	c7 05 5c ba 5b 06 00 	mov    DWORD PTR ds:0x65bba5c,0x0
  4df37e:	00 00 00 
  4df381:	e8 0a bc 02 00       	call   0x50af90
  4df386:	83 3d d8 bc 5b 06 00 	cmp    DWORD PTR ds:0x65bbcd8,0x0
  4df38d:	74 17                	je     0x4df3a6
  4df38f:	e8 ac 0c 03 00       	call   0x510040
  4df394:	a1 d8 bc 5b 06       	mov    eax,ds:0x65bbcd8
  4df399:	33 c9                	xor    ecx,ecx
  4df39b:	83 f8 02             	cmp    eax,0x2
  4df39e:	0f 44 c1             	cmove  eax,ecx
  4df3a1:	a3 d8 bc 5b 06       	mov    ds:0x65bbcd8,eax
  4df3a6:	e8 15 c0 02 00       	call   0x50b3c0
  4df3ab:	83 3d 54 1c 5c 0a 00 	cmp    DWORD PTR ds:0xa5c1c54,0x0
  4df3b2:	75 0f                	jne    0x4df3c3
  4df3b4:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4df3ba:	ff 15 7c c2 58 00    	call   DWORD PTR ds:0x58c27c
  4df3c0:	83 c4 04             	add    esp,0x4
  4df3c3:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4df3ca:	00 
  4df3cb:	b9 0a 00 00 00       	mov    ecx,0xa
  4df3d0:	8b 15 b0 ac 35 06    	mov    edx,DWORD PTR ds:0x635acb0
  4df3d6:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4df3d9:	68 70 50 59 00       	push   0x595070
  4df3de:	f3 0f 59 05 98 d4 5d 	mulss  xmm0,DWORD PTR ds:0x5dd498
  4df3e5:	00 
  4df3e6:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4df3ea:	2b d0                	sub    edx,eax
  4df3ec:	03 15 a8 ac 35 06    	add    edx,DWORD PTR ds:0x635aca8
  4df3f2:	e8 89 52 03 00       	call   0x514680
  4df3f7:	83 c4 04             	add    esp,0x4
  4df3fa:	e8 81 48 ff ff       	call   0x4d3c80
  4df3ff:	b9 48 66 5a 00       	mov    ecx,0x5a6648
  4df404:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4df40b:	00 00 00 
  4df40e:	e8 7d d2 02 00       	call   0x50c690
  4df413:	e9 1b f8 ff ff       	jmp    0x4dec33
  4df418:	b9 48 66 5a 00       	mov    ecx,0x5a6648
  4df41d:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4df424:	00 00 00 
  4df427:	e8 64 d2 02 00       	call   0x50c690
  4df42c:	8b 9d 58 fa ff ff    	mov    ebx,DWORD PTR [ebp-0x5a8]
  4df432:	89 9d 64 fa ff ff    	mov    DWORD PTR [ebp-0x59c],ebx
  4df438:	e9 f6 f7 ff ff       	jmp    0x4dec33
  4df43d:	b9 48 66 5a 00       	mov    ecx,0x5a6648
  4df442:	e8 79 d0 02 00       	call   0x50c4c0
  4df447:	b9 58 63 5a 00       	mov    ecx,0x5a6358
  4df44c:	e8 ff bd 02 00       	call   0x50b250
  4df451:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4df454:	5f                   	pop    edi
  4df455:	5e                   	pop    esi
  4df456:	33 cd                	xor    ecx,ebp
  4df458:	5b                   	pop    ebx
  4df459:	e8 50 ac 0a 00       	call   0x58a0ae
  4df45e:	8b e5                	mov    esp,ebp
  4df460:	5d                   	pop    ebp
  4df461:	c3                   	ret
  4df462:	cc                   	int3
  4df463:	cc                   	int3
  4df464:	cc                   	int3
  4df465:	cc                   	int3
  4df466:	cc                   	int3
  4df467:	cc                   	int3
  4df468:	cc                   	int3
  4df469:	cc                   	int3
  4df46a:	cc                   	int3
  4df46b:	cc                   	int3
  4df46c:	cc                   	int3
  4df46d:	cc                   	int3
  4df46e:	cc                   	int3
  4df46f:	cc                   	int3

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

005157b0 <.text+0x1147b0>:
  5157b0:	55                   	push   ebp
  5157b1:	8b ec                	mov    ebp,esp
  5157b3:	83 e4 f8             	and    esp,0xfffffff8
  5157b6:	83 ec 14             	sub    esp,0x14
  5157b9:	53                   	push   ebx
  5157ba:	56                   	push   esi
  5157bb:	8b 35 f8 c1 58 00    	mov    esi,DWORD PTR ds:0x58c1f8
  5157c1:	8b d9                	mov    ebx,ecx
  5157c3:	57                   	push   edi
  5157c4:	8b fa                	mov    edi,edx
  5157c6:	6a 54                	push   0x54
  5157c8:	8d 43 05             	lea    eax,[ebx+0x5]
  5157cb:	89 7c 24 18          	mov    DWORD PTR [esp+0x18],edi
  5157cf:	89 44 24 1c          	mov    DWORD PTR [esp+0x1c],eax
  5157d3:	8d 47 04             	lea    eax,[edi+0x4]
  5157d6:	89 44 24 20          	mov    DWORD PTR [esp+0x20],eax
  5157da:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  5157df:	68 fc 00 00 00       	push   0xfc
  5157e4:	68 fc 00 00 00       	push   0xfc
  5157e9:	ff 70 04             	push   DWORD PTR [eax+0x4]
  5157ec:	ff d6                	call   esi
  5157ee:	8b 4d 10             	mov    ecx,DWORD PTR [ebp+0x10]
  5157f1:	83 c4 10             	add    esp,0x10
  5157f4:	49                   	dec    ecx
  5157f5:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  5157f9:	83 f9 09             	cmp    ecx,0x9
  5157fc:	0f 87 ed 01 00 00    	ja     0x5159ef
  515802:	ff 24 8d a4 5a 51 00 	jmp    DWORD PTR [ecx*4+0x515aa4]
  515809:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  51580e:	68 98 00 00 00       	push   0x98
  515813:	6a 5a                	push   0x5a
  515815:	6a 3c                	push   0x3c
  515817:	ff 70 04             	push   DWORD PTR [eax+0x4]
  51581a:	ff d6                	call   esi
  51581c:	05 00 10 00 00       	add    eax,0x1000
  515821:	8b d7                	mov    edx,edi
  515823:	50                   	push   eax
  515824:	68 16 c6 58 00       	push   0x58c616
  515829:	6a 10                	push   0x10
  51582b:	ff 75 08             	push   DWORD PTR [ebp+0x8]
  51582e:	8b cb                	mov    ecx,ebx
  515830:	e8 3b 06 00 00       	call   0x515e70
  515835:	8b 75 0c             	mov    esi,DWORD PTR [ebp+0xc]
  515838:	83 c4 20             	add    esp,0x20
  51583b:	8b ce                	mov    ecx,esi
  51583d:	8d 51 01             	lea    edx,[ecx+0x1]
  515840:	8a 01                	mov    al,BYTE PTR [ecx]
  515842:	41                   	inc    ecx
  515843:	84 c0                	test   al,al
  515845:	75 f9                	jne    0x515840
  515847:	2b ca                	sub    ecx,edx
  515849:	8d 04 cd 00 00 00 00 	lea    eax,[ecx*8+0x0]
  515850:	99                   	cdq
  515851:	2b c2                	sub    eax,edx
  515853:	8b c8                	mov    ecx,eax
  515855:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
  515858:	99                   	cdq
  515859:	2b c2                	sub    eax,edx
  51585b:	d1 f9                	sar    ecx,1
  51585d:	d1 f8                	sar    eax,1
  51585f:	2b c1                	sub    eax,ecx
  515861:	83 c0 05             	add    eax,0x5
  515864:	03 c3                	add    eax,ebx
  515866:	89 44 24 18          	mov    DWORD PTR [esp+0x18],eax
  51586a:	e9 15 02 00 00       	jmp    0x515a84
  51586f:	51                   	push   ecx
  515870:	6a 0f                	push   0xf
  515872:	ff 75 08             	push   DWORD PTR [ebp+0x8]
  515875:	8b d7                	mov    edx,edi
  515877:	8b cb                	mov    ecx,ebx
  515879:	e8 02 bc ff ff       	call   0x511480
  51587e:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  515883:	83 c4 0c             	add    esp,0xc
  515886:	68 de 00 00 00       	push   0xde
  51588b:	68 c4 00 00 00       	push   0xc4
  515890:	68 b0 00 00 00       	push   0xb0
  515895:	ff 70 04             	push   DWORD PTR [eax+0x4]
  515898:	ff d6                	call   esi
  51589a:	8b 75 0c             	mov    esi,DWORD PTR [ebp+0xc]
  51589d:	83 c4 10             	add    esp,0x10
  5158a0:	e9 e3 01 00 00       	jmp    0x515a88
  5158a5:	68 ff 00 00 00       	push   0xff
  5158aa:	ff 35 70 10 61 0a    	push   DWORD PTR ds:0xa611070
  5158b0:	8b 75 08             	mov    esi,DWORD PTR [ebp+0x8]
  5158b3:	8b d7                	mov    edx,edi
  5158b5:	6a 10                	push   0x10
  5158b7:	56                   	push   esi
  5158b8:	8b cb                	mov    ecx,ebx
  5158ba:	e8 41 80 ff ff       	call   0x50d900
  5158bf:	8d 47 0f             	lea    eax,[edi+0xf]
  5158c2:	c7 05 68 10 61 0a 00 	mov    DWORD PTR ds:0xa611068,0x0
  5158c9:	00 00 00 
  5158cc:	50                   	push   eax
  5158cd:	8d 46 ff             	lea    eax,[esi-0x1]
  5158d0:	8b d7                	mov    edx,edi
  5158d2:	03 c3                	add    eax,ebx
  5158d4:	8b cb                	mov    ecx,ebx
  5158d6:	50                   	push   eax
  5158d7:	e8 64 8c ff ff       	call   0x50e540
  5158dc:	83 c4 18             	add    esp,0x18
  5158df:	e9 9d 01 00 00       	jmp    0x515a81
  5158e4:	68 80 00 00 00       	push   0x80
  5158e9:	6a 00                	push   0x0
  5158eb:	eb c3                	jmp    0x5158b0
  5158ed:	8b 75 08             	mov    esi,DWORD PTR [ebp+0x8]
  5158f0:	8b d7                	mov    edx,edi
  5158f2:	68 ff 00 00 00       	push   0xff
  5158f7:	ff 35 70 10 61 0a    	push   DWORD PTR ds:0xa611070
  5158fd:	8b cb                	mov    ecx,ebx
  5158ff:	6a 10                	push   0x10
  515901:	56                   	push   esi
  515902:	e8 f9 7f ff ff       	call   0x50d900
  515907:	8d 47 0f             	lea    eax,[edi+0xf]
  51590a:	c7 05 68 10 61 0a 00 	mov    DWORD PTR ds:0xa611068,0x0
  515911:	00 00 00 
  515914:	50                   	push   eax
  515915:	8d 46 ff             	lea    eax,[esi-0x1]
  515918:	8b d7                	mov    edx,edi
  51591a:	03 c3                	add    eax,ebx
  51591c:	8b cb                	mov    ecx,ebx
  51591e:	50                   	push   eax
  51591f:	e8 1c 8c ff ff       	call   0x50e540
  515924:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  515929:	68 8c 00 00 00       	push   0x8c
  51592e:	68 e6 00 00 00       	push   0xe6
  515933:	68 f0 00 00 00       	push   0xf0
  515938:	ff 70 04             	push   DWORD PTR [eax+0x4]
  51593b:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  515941:	8b 75 0c             	mov    esi,DWORD PTR [ebp+0xc]
  515944:	83 c4 28             	add    esp,0x28
  515947:	e9 3c 01 00 00       	jmp    0x515a88
  51594c:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  515951:	68 ff 00 00 00       	push   0xff
  515956:	6a 28                	push   0x28
  515958:	6a 28                	push   0x28
  51595a:	6a 28                	push   0x28
  51595c:	ff 70 04             	push   DWORD PTR [eax+0x4]
  51595f:	ff d6                	call   esi
  515961:	83 c4 10             	add    esp,0x10
  515964:	8b d7                	mov    edx,edi
  515966:	8b cb                	mov    ecx,ebx
  515968:	50                   	push   eax
  515969:	6a 10                	push   0x10
  51596b:	ff 75 08             	push   DWORD PTR [ebp+0x8]
  51596e:	e8 8d 7f ff ff       	call   0x50d900
  515973:	8d 47 0f             	lea    eax,[edi+0xf]
  515976:	c7 05 68 10 61 0a 00 	mov    DWORD PTR ds:0xa611068,0x0
  51597d:	00 00 00 
  515980:	50                   	push   eax
  515981:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
  515984:	8b d7                	mov    edx,edi
  515986:	48                   	dec    eax
  515987:	8b cb                	mov    ecx,ebx
  515989:	03 c3                	add    eax,ebx
  51598b:	50                   	push   eax
  51598c:	e8 af 8b ff ff       	call   0x50e540
  515991:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  515996:	68 ff 00 00 00       	push   0xff
  51599b:	68 ff 00 00 00       	push   0xff
  5159a0:	68 ff 00 00 00       	push   0xff
  5159a5:	ff 70 04             	push   DWORD PTR [eax+0x4]
  5159a8:	ff d6                	call   esi
  5159aa:	8b 75 0c             	mov    esi,DWORD PTR [ebp+0xc]
  5159ad:	83 c4 28             	add    esp,0x28
  5159b0:	8b ce                	mov    ecx,esi
  5159b2:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  5159b6:	8d 51 01             	lea    edx,[ecx+0x1]
  5159b9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  5159c0:	8a 01                	mov    al,BYTE PTR [ecx]
  5159c2:	41                   	inc    ecx
  5159c3:	84 c0                	test   al,al
  5159c5:	75 f9                	jne    0x5159c0
  5159c7:	2b ca                	sub    ecx,edx
  5159c9:	8d 04 cd 00 00 00 00 	lea    eax,[ecx*8+0x0]
  5159d0:	99                   	cdq
  5159d1:	2b c2                	sub    eax,edx
  5159d3:	8b c8                	mov    ecx,eax
  5159d5:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
  5159d8:	99                   	cdq
  5159d9:	2b c2                	sub    eax,edx
  5159db:	d1 f9                	sar    ecx,1
  5159dd:	d1 f8                	sar    eax,1
  5159df:	2b c1                	sub    eax,ecx
  5159e1:	83 c0 05             	add    eax,0x5
  5159e4:	03 c3                	add    eax,ebx
  5159e6:	89 44 24 18          	mov    DWORD PTR [esp+0x18],eax
  5159ea:	e9 95 00 00 00       	jmp    0x515a84
  5159ef:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  5159f4:	6a 20                	push   0x20
  5159f6:	68 ff 00 00 00       	push   0xff
  5159fb:	68 ff 00 00 00       	push   0xff
  515a00:	68 ff 00 00 00       	push   0xff
  515a05:	ff 70 04             	push   DWORD PTR [eax+0x4]
  515a08:	ff d6                	call   esi
  515a0a:	8b 75 08             	mov    esi,DWORD PTR [ebp+0x8]
  515a0d:	83 c4 10             	add    esp,0x10
  515a10:	8b d7                	mov    edx,edi
  515a12:	8b cb                	mov    ecx,ebx
  515a14:	50                   	push   eax
  515a15:	6a 10                	push   0x10
  515a17:	56                   	push   esi
  515a18:	e8 e3 7e ff ff       	call   0x50d900
  515a1d:	8b 44 24 24          	mov    eax,DWORD PTR [esp+0x24]
  515a21:	4e                   	dec    esi
  515a22:	6a 00                	push   0x0
  515a24:	50                   	push   eax
  515a25:	03 f3                	add    esi,ebx
  515a27:	c7 05 68 10 61 0a 00 	mov    DWORD PTR ds:0xa611068,0x0
  515a2e:	00 00 00 
  515a31:	56                   	push   esi
  515a32:	8b d0                	mov    edx,eax
  515a34:	8b cb                	mov    ecx,ebx
  515a36:	83 c7 0f             	add    edi,0xf
  515a39:	e8 02 e9 ff ff       	call   0x514340
  515a3e:	83 c4 1c             	add    esp,0x1c
  515a41:	8b d7                	mov    edx,edi
  515a43:	8b cb                	mov    ecx,ebx
  515a45:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  515a4b:	57                   	push   edi
  515a4c:	56                   	push   esi
  515a4d:	e8 ee e8 ff ff       	call   0x514340
  515a52:	8b 54 24 20          	mov    edx,DWORD PTR [esp+0x20]
  515a56:	83 c4 0c             	add    esp,0xc
  515a59:	8b cb                	mov    ecx,ebx
  515a5b:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  515a61:	57                   	push   edi
  515a62:	53                   	push   ebx
  515a63:	e8 d8 e8 ff ff       	call   0x514340
  515a68:	8b 54 24 20          	mov    edx,DWORD PTR [esp+0x20]
  515a6c:	83 c4 0c             	add    esp,0xc
  515a6f:	8b ce                	mov    ecx,esi
  515a71:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  515a77:	57                   	push   edi
  515a78:	56                   	push   esi
  515a79:	e8 c2 e8 ff ff       	call   0x514340
  515a7e:	83 c4 0c             	add    esp,0xc
  515a81:	8b 75 0c             	mov    esi,DWORD PTR [ebp+0xc]
  515a84:	8b 44 24 10          	mov    eax,DWORD PTR [esp+0x10]
  515a88:	8b 54 24 1c          	mov    edx,DWORD PTR [esp+0x1c]
  515a8c:	8b 4c 24 18          	mov    ecx,DWORD PTR [esp+0x18]
  515a90:	6a 01                	push   0x1
  515a92:	50                   	push   eax
  515a93:	56                   	push   esi
  515a94:	e8 07 8b ff ff       	call   0x50e5a0
  515a99:	83 c4 0c             	add    esp,0xc
  515a9c:	5f                   	pop    edi
  515a9d:	5e                   	pop    esi
  515a9e:	5b                   	pop    ebx
  515a9f:	8b e5                	mov    esp,ebp
  515aa1:	5d                   	pop    ebp
  515aa2:	c3                   	ret
  515aa3:	90                   	nop
  515aa4:	a5                   	movs   DWORD PTR es:[edi],DWORD PTR ds:[esi]
  515aa5:	58                   	pop    eax
  515aa6:	51                   	push   ecx
  515aa7:	00 e4                	add    ah,ah
  515aa9:	58                   	pop    eax
  515aaa:	51                   	push   ecx
  515aab:	00 ef                	add    bh,ch
  515aad:	59                   	pop    ecx
  515aae:	51                   	push   ecx
	...
