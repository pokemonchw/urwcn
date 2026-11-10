
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004903d1 <.text+0x8f3d1>:
  4903d1:	8b 95 84 f9 ff ff    	mov    edx,DWORD PTR [ebp-0x67c]
  4903d7:	83 c4 0c             	add    esp,0xc
  4903da:	69 f0 48 0c 00 00    	imul   esi,eax,0xc48
  4903e0:	8b cf                	mov    ecx,edi
  4903e2:	a1 c4 9b 5a 06       	mov    eax,ds:0x65a9bc4
  4903e7:	89 86 1c 52 78 0a    	mov    DWORD PTR [esi+0xa78521c],eax
  4903ed:	a1 c8 9b 5a 06       	mov    eax,ds:0x65a9bc8
  4903f2:	89 86 20 52 78 0a    	mov    DWORD PTR [esi+0xa785220],eax
  4903f8:	a1 cc 9b 5a 06       	mov    eax,ds:0x65a9bcc
  4903fd:	89 86 24 52 78 0a    	mov    DWORD PTR [esi+0xa785224],eax
  490403:	a1 d0 9b 5a 06       	mov    eax,ds:0x65a9bd0
  490408:	89 86 28 52 78 0a    	mov    DWORD PTR [esi+0xa785228],eax
  49040e:	c7 86 30 52 78 0a 05 	mov    DWORD PTR [esi+0xa785230],0x5
  490415:	00 00 00 
  490418:	e8 03 71 f7 ff       	call   0x407520
  49041d:	8d 96 34 52 78 0a    	lea    edx,[esi+0xa785234]
  490423:	8b fa                	mov    edi,edx
  490425:	2b f8                	sub    edi,eax
  490427:	8a 08                	mov    cl,BYTE PTR [eax]
  490429:	8d 40 01             	lea    eax,[eax+0x1]
  49042c:	88 4c 07 ff          	mov    BYTE PTR [edi+eax*1-0x1],cl
  490430:	84 c9                	test   cl,cl
  490432:	75 f3                	jne    0x490427
  490434:	a1 a4 87 5e 00       	mov    eax,ds:0x5e87a4
  490439:	8d 4a 01             	lea    ecx,[edx+0x1]
  49043c:	89 86 3c 56 78 0a    	mov    DWORD PTR [esi+0xa78563c],eax
  490442:	8a 02                	mov    al,BYTE PTR [edx]
  490444:	42                   	inc    edx
  490445:	84 c0                	test   al,al
  490447:	75 f9                	jne    0x490442
  490449:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  490450:	00 
  490451:	2b d1                	sub    edx,ecx
  490453:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  490456:	8d 04 d5 00 00 00 00 	lea    eax,[edx*8+0x0]
  49045d:	99                   	cdq
  49045e:	2b c2                	sub    eax,edx
  490460:	f3 0f 59 05 00 d2 5d 	mulss  xmm0,DWORD PTR ds:0x5dd200
  490467:	00 
  490468:	8b c8                	mov    ecx,eax
  49046a:	a1 cc 9b 5a 06       	mov    eax,ds:0x65a9bcc
  49046f:	99                   	cdq
  490470:	2b c2                	sub    eax,edx
  490472:	d1 f9                	sar    ecx,1
  490474:	d1 f8                	sar    eax,1
  490476:	2b c1                	sub    eax,ecx
  490478:	8b 0d c8 9b 5a 06    	mov    ecx,DWORD PTR ds:0x65a9bc8
  49047e:	03 05 c4 9b 5a 06    	add    eax,DWORD PTR ds:0x65a9bc4
  490484:	89 86 34 56 78 0a    	mov    DWORD PTR [esi+0xa785634],eax
  49048a:	f3 0f 2c c0          	cvttss2si eax,xmm0
  49048e:	2b c8                	sub    ecx,eax
  490490:	03 0d d0 9b 5a 06    	add    ecx,DWORD PTR ds:0x65a9bd0
  490496:	89 8e 38 56 78 0a    	mov    DWORD PTR [esi+0xa785638],ecx
