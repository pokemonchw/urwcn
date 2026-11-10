
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0050b3c0 <.text+0x10a3c0>:
  50b3c0:	55                   	push   ebp
  50b3c1:	8b ec                	mov    ebp,esp
  50b3c3:	83 ec 1c             	sub    esp,0x1c
  50b3c6:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  50b3cb:	33 c5                	xor    eax,ebp
  50b3cd:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  50b3d0:	53                   	push   ebx
  50b3d1:	56                   	push   esi
  50b3d2:	57                   	push   edi
  50b3d3:	be 1c 52 78 0a       	mov    esi,0xa78521c
  50b3d8:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  50b3df:	00 
  50b3e0:	8b 8e dc f7 ff ff    	mov    ecx,DWORD PTR [esi-0x824]
  50b3e6:	85 c9                	test   ecx,ecx
  50b3e8:	74 6d                	je     0x50b457
  50b3ea:	80 7e 10 00          	cmp    BYTE PTR [esi+0x10],0x0
  50b3ee:	75 67                	jne    0x50b457
  50b3f0:	8b 16                	mov    edx,DWORD PTR [esi]
  50b3f2:	85 d2                	test   edx,edx
  50b3f4:	75 19                	jne    0x50b40f
  50b3f6:	0f 28 05 70 d9 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd970
  50b3fd:	0f 11 45 ec          	movups XMMWORD PTR [ebp-0x14],xmm0
  50b401:	8b 45 f8             	mov    eax,DWORD PTR [ebp-0x8]
  50b404:	8b 7d f4             	mov    edi,DWORD PTR [ebp-0xc]
  50b407:	8b 5d f0             	mov    ebx,DWORD PTR [ebp-0x10]
  50b40a:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  50b40d:	eb 09                	jmp    0x50b418
  50b40f:	8b 5e 04             	mov    ebx,DWORD PTR [esi+0x4]
  50b412:	8b 7e 08             	mov    edi,DWORD PTR [esi+0x8]
  50b415:	8b 46 0c             	mov    eax,DWORD PTR [esi+0xc]
  50b418:	ff 76 14             	push   DWORD PTR [esi+0x14]
  50b41b:	50                   	push   eax
  50b41c:	57                   	push   edi
  50b41d:	53                   	push   ebx
  50b41e:	e8 dd 7d 00 00       	call   0x513200
  50b423:	8d 56 18             	lea    edx,[esi+0x18]
  50b426:	83 c4 10             	add    esp,0x10
  50b429:	8b c2                	mov    eax,edx
  50b42b:	8d 78 01             	lea    edi,[eax+0x1]
  50b42e:	66 90                	xchg   ax,ax
  50b430:	8a 08                	mov    cl,BYTE PTR [eax]
  50b432:	40                   	inc    eax
  50b433:	84 c9                	test   cl,cl
  50b435:	75 f9                	jne    0x50b430
  50b437:	2b c7                	sub    eax,edi
  50b439:	74 1c                	je     0x50b457
  50b43b:	51                   	push   ecx
  50b43c:	ff b6 20 04 00 00    	push   DWORD PTR [esi+0x420]
  50b442:	52                   	push   edx
  50b443:	ff b6 1c 04 00 00    	push   DWORD PTR [esi+0x41c]
  50b449:	8b 96 18 04 00 00    	mov    edx,DWORD PTR [esi+0x418]
  50b44f:	e8 8c 2f 00 00       	call   0x50e3e0
  50b454:	83 c4 10             	add    esp,0x10
  50b457:	81 c6 48 0c 00 00    	add    esi,0xc48
  50b45d:	81 fe 1c 76 7e 0a    	cmp    esi,0xa7e761c
  50b463:	0f 8c 77 ff ff ff    	jl     0x50b3e0
  50b469:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  50b46c:	5f                   	pop    edi
  50b46d:	5e                   	pop    esi
  50b46e:	33 cd                	xor    ecx,ebp
  50b470:	5b                   	pop    ebx
  50b471:	e8 38 ec 07 00       	call   0x58a0ae
  50b476:	8b e5                	mov    esp,ebp
  50b478:	5d                   	pop    ebp
  50b479:	c3                   	ret
