; Windows 3.89.1 original PE, preferred VA base 00400000.
; Static disassembly only; no game execution.


/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0043c8a0 <.text+0x3b8a0>:
  43c8a0:	55                   	push   ebp
  43c8a1:	8b ec                	mov    ebp,esp
  43c8a3:	83 ec 68             	sub    esp,0x68
  43c8a6:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  43c8ab:	33 c5                	xor    eax,ebp
  43c8ad:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  43c8b0:	53                   	push   ebx
  43c8b1:	56                   	push   esi
  43c8b2:	6a 64                	push   0x64
  43c8b4:	8d 45 98             	lea    eax,[ebp-0x68]
  43c8b7:	8b f1                	mov    esi,ecx
  43c8b9:	6a 00                	push   0x0
  43c8bb:	50                   	push   eax
  43c8bc:	e8 9f e5 14 00       	call   0x58ae60
  43c8c1:	83 c4 0c             	add    esp,0xc
  43c8c4:	8b ce                	mov    ecx,esi
  43c8c6:	e8 e5 74 09 00       	call   0x4d3db0
  43c8cb:	8d 55 98             	lea    edx,[ebp-0x68]
  43c8ce:	2b d0                	sub    edx,eax
  43c8d0:	8a 08                	mov    cl,BYTE PTR [eax]
  43c8d2:	8d 40 01             	lea    eax,[eax+0x1]
  43c8d5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  43c8d9:	84 c9                	test   cl,cl
  43c8db:	75 f3                	jne    0x43c8d0
  43c8dd:	be d8 ad 69 00       	mov    esi,0x69add8
  43c8e2:	8b d6                	mov    edx,esi
  43c8e4:	8d 4a 01             	lea    ecx,[edx+0x1]
  43c8e7:	8a 02                	mov    al,BYTE PTR [edx]
  43c8e9:	42                   	inc    edx
  43c8ea:	84 c0                	test   al,al
  43c8ec:	75 f9                	jne    0x43c8e7
  43c8ee:	2b d1                	sub    edx,ecx
  43c8f0:	8d 45 98             	lea    eax,[ebp-0x68]
  43c8f3:	8b ce                	mov    ecx,esi
  43c8f5:	8a 19                	mov    bl,BYTE PTR [ecx]
  43c8f7:	3a 18                	cmp    bl,BYTE PTR [eax]
  43c8f9:	75 1a                	jne    0x43c915
  43c8fb:	84 db                	test   bl,bl
  43c8fd:	74 12                	je     0x43c911
  43c8ff:	8a 59 01             	mov    bl,BYTE PTR [ecx+0x1]
  43c902:	3a 58 01             	cmp    bl,BYTE PTR [eax+0x1]
  43c905:	75 0e                	jne    0x43c915
  43c907:	83 c1 02             	add    ecx,0x2
  43c90a:	83 c0 02             	add    eax,0x2
  43c90d:	84 db                	test   bl,bl
  43c90f:	75 e4                	jne    0x43c8f5
  43c911:	33 c0                	xor    eax,eax
  43c913:	eb 05                	jmp    0x43c91a
  43c915:	1b c0                	sbb    eax,eax
  43c917:	83 c8 01             	or     eax,0x1
  43c91a:	33 c9                	xor    ecx,ecx
  43c91c:	85 c0                	test   eax,eax
  43c91e:	0f 94 c1             	sete   cl
  43c921:	33 c0                	xor    eax,eax
  43c923:	3b c2                	cmp    eax,edx
  43c925:	1b c0                	sbb    eax,eax
  43c927:	f7 d8                	neg    eax
  43c929:	85 c8                	test   eax,ecx
  43c92b:	75 20                	jne    0x43c94d
  43c92d:	81 c6 c8 00 00 00    	add    esi,0xc8
  43c933:	81 fe 18 bb 6c 00    	cmp    esi,0x6cbb18
  43c939:	7c a7                	jl     0x43c8e2
  43c93b:	5e                   	pop    esi
  43c93c:	33 c0                	xor    eax,eax
  43c93e:	5b                   	pop    ebx
  43c93f:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  43c942:	33 cd                	xor    ecx,ebp
  43c944:	e8 65 d7 14 00       	call   0x58a0ae
  43c949:	8b e5                	mov    esp,ebp
  43c94b:	5d                   	pop    ebp
  43c94c:	c3                   	ret
  43c94d:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  43c950:	b8 01 00 00 00       	mov    eax,0x1
  43c955:	5e                   	pop    esi
  43c956:	33 cd                	xor    ecx,ebp
  43c958:	5b                   	pop    ebx
  43c959:	e8 50 d7 14 00       	call   0x58a0ae
  43c95e:	8b e5                	mov    esp,ebp
  43c960:	5d                   	pop    ebp
  43c961:	c3                   	ret


/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0043dd10 <.text+0x3cd10>:
  43dd10:	55                   	push   ebp
  43dd11:	8b ec                	mov    ebp,esp
  43dd13:	81 ec fc 05 00 00    	sub    esp,0x5fc
  43dd19:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  43dd1e:	33 c5                	xor    eax,ebp
  43dd20:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  43dd23:	53                   	push   ebx
  43dd24:	56                   	push   esi
  43dd25:	57                   	push   edi
  43dd26:	68 2c 01 00 00       	push   0x12c
  43dd2b:	8d 85 08 fa ff ff    	lea    eax,[ebp-0x5f8]
  43dd31:	8b f1                	mov    esi,ecx
  43dd33:	6a 00                	push   0x0
  43dd35:	50                   	push   eax
  43dd36:	e8 25 d1 14 00       	call   0x58ae60
  43dd3b:	83 c4 0c             	add    esp,0xc
  43dd3e:	8d 85 c8 fe ff ff    	lea    eax,[ebp-0x138]
  43dd44:	68 2c 01 00 00       	push   0x12c
  43dd49:	6a 00                	push   0x0
  43dd4b:	50                   	push   eax
  43dd4c:	e8 0f d1 14 00       	call   0x58ae60
  43dd51:	83 c4 0c             	add    esp,0xc
  43dd54:	8d 85 68 fc ff ff    	lea    eax,[ebp-0x398]
  43dd5a:	68 2c 01 00 00       	push   0x12c
  43dd5f:	6a 00                	push   0x0
  43dd61:	50                   	push   eax
  43dd62:	e8 f9 d0 14 00       	call   0x58ae60
  43dd67:	83 c4 0c             	add    esp,0xc
  43dd6a:	8d 85 98 fd ff ff    	lea    eax,[ebp-0x268]
  43dd70:	68 2c 01 00 00       	push   0x12c
  43dd75:	6a 00                	push   0x0
  43dd77:	50                   	push   eax
  43dd78:	e8 e3 d0 14 00       	call   0x58ae60
  43dd7d:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  43dd82:	83 c4 0c             	add    esp,0xc
  43dd85:	6a 64                	push   0x64
  43dd87:	68 58 02 00 00       	push   0x258
  43dd8c:	68 20 03 00 00       	push   0x320
  43dd91:	6a 00                	push   0x0
  43dd93:	6a 00                	push   0x0
  43dd95:	6a 54                	push   0x54
  43dd97:	68 fc 00 00 00       	push   0xfc
  43dd9c:	68 fc 00 00 00       	push   0xfc
  43dda1:	ff 70 04             	push   DWORD PTR [eax+0x4]
  43dda4:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  43ddaa:	83 c4 10             	add    esp,0x10
  43ddad:	ba 16 c6 58 00       	mov    edx,0x58c616
  43ddb2:	8b c8                	mov    ecx,eax
  43ddb4:	e8 d7 19 09 00       	call   0x4cf790
  43ddb9:	83 c4 14             	add    esp,0x14
  43ddbc:	c7 05 9c 4a 35 06 01 	mov    DWORD PTR ds:0x6354a9c,0x1
  43ddc3:	00 00 00 
  43ddc6:	8b ce                	mov    ecx,esi
  43ddc8:	c7 05 a0 4a 35 06 01 	mov    DWORD PTR ds:0x6354aa0,0x1
  43ddcf:	00 00 00 
  43ddd2:	c7 05 c0 4a 35 06 01 	mov    DWORD PTR ds:0x6354ac0,0x1
  43ddd9:	00 00 00 
  43dddc:	e8 cf 5f 09 00       	call   0x4d3db0
  43dde1:	8d 95 98 fd ff ff    	lea    edx,[ebp-0x268]
  43dde7:	2b d0                	sub    edx,eax
  43dde9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  43ddf0:	8a 08                	mov    cl,BYTE PTR [eax]
  43ddf2:	8d 40 01             	lea    eax,[eax+0x1]
  43ddf5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  43ddf9:	84 c9                	test   cl,cl
  43ddfb:	75 f3                	jne    0x43ddf0
  43ddfd:	8d 8d 98 fd ff ff    	lea    ecx,[ebp-0x268]
  43de03:	8d 51 01             	lea    edx,[ecx+0x1]
  43de06:	8a 01                	mov    al,BYTE PTR [ecx]
  43de08:	41                   	inc    ecx
  43de09:	84 c0                	test   al,al
  43de0b:	75 f9                	jne    0x43de06
  43de0d:	2b ca                	sub    ecx,edx
  43de0f:	83 f9 03             	cmp    ecx,0x3
  43de12:	0f 82 ac 02 00 00    	jb     0x43e0c4


/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0043df09 <.text+0x3cf09>:
  43df09:	8d 8d 98 fd ff ff    	lea    ecx,[ebp-0x268]
  43df0f:	e8 0c e9 ff ff       	call   0x43c820
  43df14:	6a 00                	push   0x0
  43df16:	6a 02                	push   0x2
  43df18:	8d 85 98 fd ff ff    	lea    eax,[ebp-0x268]
  43df1e:	ba 1e 00 00 00       	mov    edx,0x1e
  43df23:	50                   	push   eax
  43df24:	68 d6 01 00 00       	push   0x1d6
  43df29:	68 bc 02 00 00       	push   0x2bc
  43df2e:	8d 4a 14             	lea    ecx,[edx+0x14]
  43df31:	e8 3a 83 0d 00       	call   0x516270
  43df36:	83 c4 14             	add    esp,0x14


/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0043e07c <.text+0x3d07c>:
  43e07c:	56                   	push   esi
  43e07d:	ff 15 b4 c4 58 00    	call   DWORD PTR ds:0x58c4b4
  43e083:	83 c4 04             	add    esp,0x4
  43e086:	33 c9                	xor    ecx,ecx
  43e088:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  43e08f:	00 
  43e090:	8a 84 0d 98 fd ff ff 	mov    al,BYTE PTR [ebp+ecx*1-0x268]
  43e097:	8d 49 01             	lea    ecx,[ecx+0x1]
  43e09a:	88 81 1f a8 6e 00    	mov    BYTE PTR [ecx+0x6ea81f],al
  43e0a0:	84 c0                	test   al,al
  43e0a2:	75 ec                	jne    0x43e090
  43e0a4:	b8 01 00 00 00       	mov    eax,0x1
  43e0a9:	5f                   	pop    edi
  43e0aa:	5e                   	pop    esi
  43e0ab:	5b                   	pop    ebx
  43e0ac:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  43e0af:	33 cd                	xor    ecx,ebp
  43e0b1:	e8 f8 bf 14 00       	call   0x58a0ae
  43e0b6:	8b e5                	mov    esp,ebp
  43e0b8:	5d                   	pop    ebp
  43e0b9:	c3                   	ret
  43e0ba:	56                   	push   esi
  43e0bb:	ff 15 b4 c4 58 00    	call   DWORD PTR ds:0x58c4b4
  43e0c1:	83 c4 04             	add    esp,0x4
  43e0c4:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  43e0c7:	33 c0                	xor    eax,eax
  43e0c9:	5f                   	pop    edi
  43e0ca:	5e                   	pop    esi
  43e0cb:	33 cd                	xor    ecx,ebp
  43e0cd:	5b                   	pop    ebx
  43e0ce:	e8 db bf 14 00       	call   0x58a0ae
  43e0d3:	8b e5                	mov    esp,ebp
  43e0d5:	5d                   	pop    ebp
  43e0d6:	c3                   	ret
  43e0d7:	ff 15 b4 c4 58 00    	call   DWORD PTR ds:0x58c4b4
  43e0dd:	83 c4 04             	add    esp,0x4
  43e0e0:	33 c9                	xor    ecx,ecx
  43e0e2:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  43e0e6:	66 66 0f 1f 84 00 00 	data16 nop WORD PTR [eax+eax*1+0x0]
  43e0ed:	00 00 00 
  43e0f0:	8a 84 0d 98 fd ff ff 	mov    al,BYTE PTR [ebp+ecx*1-0x268]
  43e0f7:	8d 49 01             	lea    ecx,[ecx+0x1]
  43e0fa:	88 81 1f a8 6e 00    	mov    BYTE PTR [ecx+0x6ea81f],al
  43e100:	84 c0                	test   al,al
  43e102:	75 ec                	jne    0x43e0f0


/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0043e2a0 <.text+0x3d2a0>:
  43e2a0:	55                   	push   ebp
  43e2a1:	8b ec                	mov    ebp,esp
  43e2a3:	83 e4 f8             	and    esp,0xfffffff8
  43e2a6:	83 ec 74             	sub    esp,0x74
  43e2a9:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  43e2ae:	33 c4                	xor    eax,esp
  43e2b0:	89 44 24 70          	mov    DWORD PTR [esp+0x70],eax
  43e2b4:	53                   	push   ebx
  43e2b5:	56                   	push   esi
  43e2b6:	57                   	push   edi
  43e2b7:	8b f9                	mov    edi,ecx
  43e2b9:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  43e2c0:	00 00 00 


/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0043e4ca <.text+0x3d4ca>:
  43e4ca:	e8 41 fc ff ff       	call   0x43e110
  43e4cf:	8b c8                	mov    ecx,eax
  43e4d1:	8d 54 24 10          	lea    edx,[esp+0x10]
  43e4d5:	2b d1                	sub    edx,ecx
  43e4d7:	8a 01                	mov    al,BYTE PTR [ecx]
  43e4d9:	8d 49 01             	lea    ecx,[ecx+0x1]
  43e4dc:	88 44 0a ff          	mov    BYTE PTR [edx+ecx*1-0x1],al
  43e4e0:	84 c0                	test   al,al
  43e4e2:	75 f3                	jne    0x43e4d7
  43e4e4:	8a 44 24 10          	mov    al,BYTE PTR [esp+0x10]
  43e4e8:	3c 20                	cmp    al,0x20
  43e4ea:	0f 85 b7 00 00 00    	jne    0x43e5a7
  43e4f0:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  43e4f5:	6a 54                	push   0x54
  43e4f7:	68 fc 00 00 00       	push   0xfc
  43e4fc:	68 fc 00 00 00       	push   0xfc
  43e501:	ff 70 04             	push   DWORD PTR [eax+0x4]
  43e504:	ff d3                	call   ebx
  43e506:	83 c4 0c             	add    esp,0xc
  43e509:	ba 3c 02 00 00       	mov    edx,0x23c
  43e50e:	b9 eb 00 00 00       	mov    ecx,0xeb
  43e513:	6a 0f                	push   0xf
  43e515:	68 90 01 00 00       	push   0x190
  43e51a:	e8 61 2f 0d 00       	call   0x511480
  43e51f:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  43e524:	83 c4 0c             	add    esp,0xc
  43e527:	68 de 00 00 00       	push   0xde
  43e52c:	68 c4 00 00 00       	push   0xc4
  43e531:	68 b0 00 00 00       	push   0xb0
  43e536:	ff 70 04             	push   DWORD PTR [eax+0x4]
  43e539:	ff d3                	call   ebx
  43e53b:	6a 01                	push   0x1
  43e53d:	50                   	push   eax
  43e53e:	68 16 c6 58 00       	push   0x58c616
  43e543:	ba 40 02 00 00       	mov    edx,0x240
  43e548:	b9 f0 00 00 00       	mov    ecx,0xf0
  43e54d:	e8 4e 00 0d 00       	call   0x50e5a0
  43e552:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  43e557:	83 c4 1c             	add    esp,0x1c
  43e55a:	c7 05 b4 1c 5c 0a f0 	mov    DWORD PTR ds:0xa5c1cb4,0xf0
  43e561:	00 00 00 
  43e564:	c7 05 3c bb 5b 06 3f 	mov    DWORD PTR ds:0x65bbb3c,0x23f
  43e56b:	02 00 00 
  43e56e:	6a 54                	push   0x54
  43e570:	68 fc 00 00 00       	push   0xfc
  43e575:	68 fc 00 00 00       	push   0xfc
  43e57a:	ff 70 04             	push   DWORD PTR [eax+0x4]
  43e57d:	ff d3                	call   ebx
  43e57f:	83 c4 10             	add    esp,0x10
  43e582:	ba 1e 00 00 00       	mov    edx,0x1e
  43e587:	8b c8                	mov    ecx,eax
  43e589:	e8 22 10 0d 00       	call   0x50f5b0
  43e58e:	8b c8                	mov    ecx,eax
  43e590:	8d 54 24 10          	lea    edx,[esp+0x10]
  43e594:	2b d1                	sub    edx,ecx
  43e596:	8a 01                	mov    al,BYTE PTR [ecx]
  43e598:	8d 49 01             	lea    ecx,[ecx+0x1]
  43e59b:	88 44 0a ff          	mov    BYTE PTR [edx+ecx*1-0x1],al
  43e59f:	84 c0                	test   al,al
  43e5a1:	75 f3                	jne    0x43e596
  43e5a3:	8a 44 24 10          	mov    al,BYTE PTR [esp+0x10]
  43e5a7:	3c 1b                	cmp    al,0x1b
  43e5a9:	75 16                	jne    0x43e5c1
  43e5ab:	33 c9                	xor    ecx,ecx
  43e5ad:	0f 1f 00             	nop    DWORD PTR [eax]
  43e5b0:	8a 81 20 a8 6e 00    	mov    al,BYTE PTR [ecx+0x6ea820]
  43e5b6:	8d 49 01             	lea    ecx,[ecx+0x1]
  43e5b9:	88 44 0c 0f          	mov    BYTE PTR [esp+ecx*1+0xf],al
  43e5bd:	84 c0                	test   al,al
  43e5bf:	75 ef                	jne    0x43e5b0
  43e5c1:	8d 44 24 10          	lea    eax,[esp+0x10]
  43e5c5:	68 ec 50 59 00       	push   0x5950ec
  43e5ca:	50                   	push   eax
  43e5cb:	ff 15 50 c3 58 00    	call   DWORD PTR ds:0x58c350
  43e5d1:	83 c4 08             	add    esp,0x8
  43e5d4:	85 c0                	test   eax,eax
  43e5d6:	0f 85 81 00 00 00    	jne    0x43e65d
  43e5dc:	8d 4c 24 10          	lea    ecx,[esp+0x10]
  43e5e0:	8d 51 01             	lea    edx,[ecx+0x1]
  43e5e3:	8a 01                	mov    al,BYTE PTR [ecx]
  43e5e5:	41                   	inc    ecx
  43e5e6:	84 c0                	test   al,al
  43e5e8:	75 f9                	jne    0x43e5e3
  43e5ea:	2b ca                	sub    ecx,edx
  43e5ec:	75 4b                	jne    0x43e639
  43e5ee:	ba 20 1f 6d 00       	mov    edx,0x6d1f20
  43e5f3:	8d 71 1d             	lea    esi,[ecx+0x1d]
  43e5f6:	8b c2                	mov    eax,edx
  43e5f8:	bb c8 00 00 00       	mov    ebx,0xc8
  43e5fd:	0f 1f 00             	nop    DWORD PTR [eax]
  43e600:	8a 08                	mov    cl,BYTE PTR [eax]
  43e602:	8d 40 01             	lea    eax,[eax+0x1]
  43e605:	88 4c 03 ff          	mov    BYTE PTR [ebx+eax*1-0x1],cl
  43e609:	84 c9                	test   cl,cl
  43e60b:	75 f3                	jne    0x43e600
  43e60d:	2b d3                	sub    edx,ebx
  43e60f:	83 ee 01             	sub    esi,0x1
  43e612:	75 e2                	jne    0x43e5f6
  43e614:	8b 1d f8 c1 58 00    	mov    ebx,DWORD PTR ds:0x58c1f8
  43e61a:	88 0d 40 09 6d 00    	mov    BYTE PTR ds:0x6d0940,cl
  43e620:	b9 e8 1f 6d 00       	mov    ecx,0x6d1fe8
  43e625:	e8 e6 f6 ff ff       	call   0x43dd10
  43e62a:	85 c0                	test   eax,eax
  43e62c:	0f 85 de fd ff ff    	jne    0x43e410
  43e632:	8b cf                	mov    ecx,edi
  43e634:	e9 cb fd ff ff       	jmp    0x43e404
  43e639:	8d 4c 24 10          	lea    ecx,[esp+0x10]
  43e63d:	e8 5e e2 ff ff       	call   0x43c8a0
  43e642:	8d 4c 24 10          	lea    ecx,[esp+0x10]
  43e646:	85 c0                	test   eax,eax
  43e648:	0f 85 b6 fd ff ff    	jne    0x43e404
  43e64e:	e8 4d f6 ff ff       	call   0x43dca0
  43e653:	b9 20 a8 6e 00       	mov    ecx,0x6ea820
  43e658:	e9 a7 fd ff ff       	jmp    0x43e404
  43e65d:	8b 4c 24 7c          	mov    ecx,DWORD PTR [esp+0x7c]
  43e661:	b8 01 00 00 00       	mov    eax,0x1
  43e666:	5f                   	pop    edi
  43e667:	5e                   	pop    esi
  43e668:	5b                   	pop    ebx
  43e669:	33 cc                	xor    ecx,esp
  43e66b:	e8 3e ba 14 00       	call   0x58a0ae
  43e670:	8b e5                	mov    esp,ebp
  43e672:	5d                   	pop    ebp
  43e673:	c3                   	ret


/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0050f5b0 <.text+0x10e5b0>:
  50f5b0:	55                   	push   ebp
  50f5b1:	8b ec                	mov    ebp,esp
  50f5b3:	81 ec bc 00 00 00    	sub    esp,0xbc
  50f5b9:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  50f5be:	33 c5                	xor    eax,ebp
  50f5c0:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  50f5c3:	53                   	push   ebx
  50f5c4:	56                   	push   esi
  50f5c5:	8b 35 b4 1c 5c 0a    	mov    esi,DWORD PTR ds:0xa5c1cb4
  50f5cb:	8b d9                	mov    ebx,ecx
  50f5cd:	57                   	push   edi
  50f5ce:	8b 3d 3c bb 5b 06    	mov    edi,DWORD PTR ds:0x65bbb3c
  50f5d4:	8b ce                	mov    ecx,esi
  50f5d6:	89 95 4c ff ff ff    	mov    DWORD PTR [ebp-0xb4],edx
  50f5dc:	89 9d 54 ff ff ff    	mov    DWORD PTR [ebp-0xac],ebx
  50f5e2:	89 b5 5c ff ff ff    	mov    DWORD PTR [ebp-0xa4],esi
  50f5e8:	8d 57 03             	lea    edx,[edi+0x3]
  50f5eb:	89 bd 48 ff ff ff    	mov    DWORD PTR [ebp-0xb8],edi
  50f5f1:	e8 9a c6 ff ff       	call   0x50bc90
  50f5f6:	6a 64                	push   0x64
  50f5f8:	6a 00                	push   0x0
  50f5fa:	68 a8 b9 89 0a       	push   0xa89b9a8
  50f5ff:	89 85 58 ff ff ff    	mov    DWORD PTR [ebp-0xa8],eax
  50f605:	e8 56 b8 07 00       	call   0x58ae60
  50f60a:	83 c4 0c             	add    esp,0xc
  50f60d:	f6 05 58 ba 5b 06 01 	test   BYTE PTR ds:0x65bba58,0x1
  50f614:	74 63                	je     0x50f679
  50f616:	33 c9                	xor    ecx,ecx
  50f618:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  50f61f:	00 
  50f620:	8a 81 60 ba 5b 06    	mov    al,BYTE PTR [ecx+0x65bba60]
  50f626:	8d 49 01             	lea    ecx,[ecx+0x1]
  50f629:	88 81 a7 b9 89 0a    	mov    BYTE PTR [ecx+0xa89b9a7],al
  50f62f:	84 c0                	test   al,al
  50f631:	75 ed                	jne    0x50f620
  50f633:	b9 a8 b9 89 0a       	mov    ecx,0xa89b9a8
  50f638:	8d 51 01             	lea    edx,[ecx+0x1]
  50f63b:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  50f640:	8a 01                	mov    al,BYTE PTR [ecx]
  50f642:	41                   	inc    ecx
  50f643:	84 c0                	test   al,al
  50f645:	75 f9                	jne    0x50f640
  50f647:	ff b5 58 ff ff ff    	push   DWORD PTR [ebp-0xa8]
  50f64d:	2b ca                	sub    ecx,edx
  50f64f:	89 75 80             	mov    DWORD PTR [ebp-0x80],esi
  50f652:	89 7d 84             	mov    DWORD PTR [ebp-0x7c],edi
  50f655:	c7 45 8c 0b 00 00 00 	mov    DWORD PTR [ebp-0x74],0xb
  50f65c:	8d 04 cd 05 00 00 00 	lea    eax,[ecx*8+0x5]
  50f663:	89 45 88             	mov    DWORD PTR [ebp-0x78],eax
  50f666:	8d 45 80             	lea    eax,[ebp-0x80]
  50f669:	50                   	push   eax
  50f66a:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  50f670:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  50f676:	83 c4 0c             	add    esp,0xc
  50f679:	6a 64                	push   0x64
  50f67b:	6a 00                	push   0x0
  50f67d:	68 60 ba 5b 06       	push   0x65bba60
  50f682:	e8 d9 b7 07 00       	call   0x58ae60
  50f687:	8d 4f 01             	lea    ecx,[edi+0x1]
  50f68a:	8b c7                	mov    eax,edi
  50f68c:	2b c1                	sub    eax,ecx
  50f68e:	83 c4 0c             	add    esp,0xc
  50f691:	83 c0 0b             	add    eax,0xb
  50f694:	89 85 50 ff ff ff    	mov    DWORD PTR [ebp-0xb0],eax
  50f69a:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  50f6a0:	6a 00                	push   0x0
  50f6a2:	53                   	push   ebx
  50f6a3:	68 a8 b9 89 0a       	push   0xa89b9a8
  50f6a8:	8b d7                	mov    edx,edi
  50f6aa:	8b ce                	mov    ecx,esi
  50f6ac:	e8 ef ee ff ff       	call   0x50e5a0
  50f6b1:	8b 35 b4 1c 5c 0a    	mov    esi,DWORD PTR ds:0xa5c1cb4
  50f6b7:	83 c4 0c             	add    esp,0xc
  50f6ba:	8b d7                	mov    edx,edi
  50f6bc:	8b ce                	mov    ecx,esi
  50f6be:	6a 00                	push   0x0
  50f6c0:	53                   	push   ebx
  50f6c1:	68 04 c9 5a 00       	push   0x5ac904
  50f6c6:	e8 d5 ee ff ff       	call   0x50e5a0
  50f6cb:	83 c4 0c             	add    esp,0xc
  50f6ce:	83 3d 5c ba 5b 06 00 	cmp    DWORD PTR ds:0x65bba5c,0x0
  50f6d5:	75 42                	jne    0x50f719
  50f6d7:	e8 b4 b8 ff ff       	call   0x50af90
  50f6dc:	83 3d d8 bc 5b 06 00 	cmp    DWORD PTR ds:0x65bbcd8,0x0
  50f6e3:	74 17                	je     0x50f6fc
  50f6e5:	e8 56 09 00 00       	call   0x510040
  50f6ea:	a1 d8 bc 5b 06       	mov    eax,ds:0x65bbcd8
  50f6ef:	33 c9                	xor    ecx,ecx
  50f6f1:	83 f8 02             	cmp    eax,0x2
  50f6f4:	0f 44 c1             	cmove  eax,ecx
  50f6f7:	a3 d8 bc 5b 06       	mov    ds:0x65bbcd8,eax
  50f6fc:	e8 bf bc ff ff       	call   0x50b3c0
  50f701:	83 3d 54 1c 5c 0a 00 	cmp    DWORD PTR ds:0xa5c1c54,0x0
  50f708:	75 0f                	jne    0x50f719
  50f70a:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  50f710:	ff 15 7c c2 58 00    	call   DWORD PTR ds:0x58c27c
  50f716:	83 c4 04             	add    esp,0x4
  50f719:	e8 d2 44 fc ff       	call   0x4d3bf0
  50f71e:	6a 64                	push   0x64
  50f720:	8b d8                	mov    ebx,eax
  50f722:	8d 45 90             	lea    eax,[ebp-0x70]
  50f725:	6a 00                	push   0x0
  50f727:	50                   	push   eax
  50f728:	e8 33 b7 07 00       	call   0x58ae60
  50f72d:	83 c4 0c             	add    esp,0xc
  50f730:	81 fb 24 04 00 00    	cmp    ebx,0x424
  50f736:	75 07                	jne    0x50f73f
  50f738:	bb 99 00 00 00       	mov    ebx,0x99
  50f73d:	eb 0e                	jmp    0x50f74d
  50f73f:	81 fb 23 04 00 00    	cmp    ebx,0x423
  50f745:	b8 8e 00 00 00       	mov    eax,0x8e
  50f74a:	0f 44 d8             	cmove  ebx,eax
  50f74d:	ff b5 58 ff ff ff    	push   DWORD PTR [ebp-0xa8]
  50f753:	8d 47 01             	lea    eax,[edi+0x1]
  50f756:	89 75 80             	mov    DWORD PTR [ebp-0x80],esi
  50f759:	89 45 84             	mov    DWORD PTR [ebp-0x7c],eax
  50f75c:	8b 85 50 ff ff ff    	mov    eax,DWORD PTR [ebp-0xb0]
  50f762:	89 45 8c             	mov    DWORD PTR [ebp-0x74],eax
  50f765:	8d 45 80             	lea    eax,[ebp-0x80]
  50f768:	50                   	push   eax
  50f769:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  50f76f:	c7 45 88 09 00 00 00 	mov    DWORD PTR [ebp-0x78],0x9
  50f776:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  50f77c:	83 c4 0c             	add    esp,0xc
  50f77f:	83 fb 08             	cmp    ebx,0x8
  50f782:	0f 85 86 00 00 00    	jne    0x50f80e
  50f788:	b9 a8 b9 89 0a       	mov    ecx,0xa89b9a8
  50f78d:	8d 51 01             	lea    edx,[ecx+0x1]
  50f790:	8a 01                	mov    al,BYTE PTR [ecx]
  50f792:	41                   	inc    ecx
  50f793:	84 c0                	test   al,al
  50f795:	75 f9                	jne    0x50f790
  50f797:	8b b5 5c ff ff ff    	mov    esi,DWORD PTR [ebp-0xa4]
  50f79d:	2b ca                	sub    ecx,edx
  50f79f:	74 73                	je     0x50f814
  50f7a1:	ff b5 58 ff ff ff    	push   DWORD PTR [ebp-0xa8]
  50f7a7:	8d 04 cd 05 00 00 00 	lea    eax,[ecx*8+0x5]
  50f7ae:	89 b5 70 ff ff ff    	mov    DWORD PTR [ebp-0x90],esi
  50f7b4:	89 85 78 ff ff ff    	mov    DWORD PTR [ebp-0x88],eax
  50f7ba:	8d 85 70 ff ff ff    	lea    eax,[ebp-0x90]
  50f7c0:	50                   	push   eax
  50f7c1:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  50f7c7:	89 bd 74 ff ff ff    	mov    DWORD PTR [ebp-0x8c],edi
  50f7cd:	c7 85 7c ff ff ff 0b 	mov    DWORD PTR [ebp-0x84],0xb
  50f7d4:	00 00 00 
  50f7d7:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  50f7dd:	b9 a8 b9 89 0a       	mov    ecx,0xa89b9a8
  50f7e2:	83 c4 0c             	add    esp,0xc
  50f7e5:	8d 51 01             	lea    edx,[ecx+0x1]
  50f7e8:	8a 01                	mov    al,BYTE PTR [ecx]
  50f7ea:	41                   	inc    ecx
  50f7eb:	84 c0                	test   al,al
  50f7ed:	75 f9                	jne    0x50f7e8
  50f7ef:	2b ca                	sub    ecx,edx
  50f7f1:	49                   	dec    ecx
  50f7f2:	83 f9 64             	cmp    ecx,0x64
  50f7f5:	0f 83 49 01 00 00    	jae    0x50f944
  50f7fb:	88 81 a8 b9 89 0a    	mov    BYTE PTR [ecx+0xa89b9a8],al
  50f801:	8b 85 54 ff ff ff    	mov    eax,DWORD PTR [ebp-0xac]
  50f807:	a3 68 10 61 0a       	mov    ds:0xa611068,eax
  50f80c:	eb 06                	jmp    0x50f814
  50f80e:	8b b5 5c ff ff ff    	mov    esi,DWORD PTR [ebp-0xa4]
  50f814:	f6 05 58 ba 5b 06 02 	test   BYTE PTR ds:0x65bba58,0x2
  50f81b:	74 15                	je     0x50f832
  50f81d:	83 fb 2a             	cmp    ebx,0x2a
  50f820:	0f 84 a2 00 00 00    	je     0x50f8c8
  50f826:	81 fb fc 03 00 00    	cmp    ebx,0x3fc
  50f82c:	0f 84 96 00 00 00    	je     0x50f8c8
  50f832:	83 fb 1b             	cmp    ebx,0x1b
  50f835:	75 09                	jne    0x50f840
  50f837:	66 89 1d a8 b9 89 0a 	mov    WORD PTR ds:0xa89b9a8,bx
  50f83e:	eb 63                	jmp    0x50f8a3
  50f840:	8d 43 e0             	lea    eax,[ebx-0x20]
  50f843:	83 f8 79             	cmp    eax,0x79
  50f846:	77 5b                	ja     0x50f8a3
  50f848:	b8 a8 b9 89 0a       	mov    eax,0xa89b9a8
  50f84d:	8d 50 01             	lea    edx,[eax+0x1]
  50f850:	8a 08                	mov    cl,BYTE PTR [eax]
  50f852:	40                   	inc    eax
  50f853:	84 c9                	test   cl,cl
  50f855:	75 f9                	jne    0x50f850
  50f857:	2b c2                	sub    eax,edx
  50f859:	3b 85 4c ff ff ff    	cmp    eax,DWORD PTR [ebp-0xb4]
  50f85f:	73 42                	jae    0x50f8a3
  50f861:	53                   	push   ebx
  50f862:	8d 45 90             	lea    eax,[ebp-0x70]
  50f865:	68 dc d6 58 00       	push   0x58d6dc
  50f86a:	50                   	push   eax
  50f86b:	e8 60 18 ef ff       	call   0x4010d0
  50f870:	8d 55 90             	lea    edx,[ebp-0x70]
  50f873:	83 c4 0c             	add    esp,0xc
  50f876:	8b f2                	mov    esi,edx
  50f878:	8a 02                	mov    al,BYTE PTR [edx]
  50f87a:	42                   	inc    edx
  50f87b:	84 c0                	test   al,al
  50f87d:	75 f9                	jne    0x50f878
  50f87f:	bf a8 b9 89 0a       	mov    edi,0xa89b9a8
  50f884:	2b d6                	sub    edx,esi
  50f886:	4f                   	dec    edi
  50f887:	8a 47 01             	mov    al,BYTE PTR [edi+0x1]
  50f88a:	47                   	inc    edi
  50f88b:	84 c0                	test   al,al
  50f88d:	75 f8                	jne    0x50f887
  50f88f:	8b ca                	mov    ecx,edx
  50f891:	c1 e9 02             	shr    ecx,0x2
  50f894:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  50f896:	8b ca                	mov    ecx,edx
  50f898:	83 e1 03             	and    ecx,0x3
  50f89b:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
  50f89d:	8b bd 48 ff ff ff    	mov    edi,DWORD PTR [ebp-0xb8]
  50f8a3:	33 c9                	xor    ecx,ecx
  50f8a5:	83 fb 1b             	cmp    ebx,0x1b
  50f8a8:	0f 95 c1             	setne  cl
  50f8ab:	33 c0                	xor    eax,eax
  50f8ad:	83 fb 0d             	cmp    ebx,0xd
  50f8b0:	0f 95 c0             	setne  al
  50f8b3:	85 c8                	test   eax,ecx
  50f8b5:	74 6d                	je     0x50f924
  50f8b7:	8b 9d 54 ff ff ff    	mov    ebx,DWORD PTR [ebp-0xac]
  50f8bd:	8b b5 5c ff ff ff    	mov    esi,DWORD PTR [ebp-0xa4]
  50f8c3:	e9 d8 fd ff ff       	jmp    0x50f6a0
  50f8c8:	b9 a8 b9 89 0a       	mov    ecx,0xa89b9a8
  50f8cd:	8d 51 01             	lea    edx,[ecx+0x1]
  50f8d0:	8a 01                	mov    al,BYTE PTR [ecx]
  50f8d2:	41                   	inc    ecx
  50f8d3:	84 c0                	test   al,al
  50f8d5:	75 f9                	jne    0x50f8d0
  50f8d7:	ff b5 58 ff ff ff    	push   DWORD PTR [ebp-0xa8]
  50f8dd:	2b ca                	sub    ecx,edx
  50f8df:	89 b5 60 ff ff ff    	mov    DWORD PTR [ebp-0xa0],esi
  50f8e5:	89 bd 64 ff ff ff    	mov    DWORD PTR [ebp-0x9c],edi
  50f8eb:	c7 85 6c ff ff ff 0b 	mov    DWORD PTR [ebp-0x94],0xb
  50f8f2:	00 00 00 
  50f8f5:	8d 04 cd 05 00 00 00 	lea    eax,[ecx*8+0x5]
  50f8fc:	8d 8d 60 ff ff ff    	lea    ecx,[ebp-0xa0]
  50f902:	89 85 68 ff ff ff    	mov    DWORD PTR [ebp-0x98],eax
  50f908:	51                   	push   ecx
  50f909:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  50f90f:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  50f915:	b9 2a 00 00 00       	mov    ecx,0x2a
  50f91a:	83 c4 0c             	add    esp,0xc
  50f91d:	66 89 0d a8 b9 89 0a 	mov    WORD PTR ds:0xa89b9a8,cx
  50f924:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  50f927:	b8 a8 b9 89 0a       	mov    eax,0xa89b9a8
  50f92c:	5f                   	pop    edi
  50f92d:	5e                   	pop    esi
  50f92e:	33 cd                	xor    ecx,ebp
  50f930:	c7 05 58 ba 5b 06 00 	mov    DWORD PTR ds:0x65bba58,0x0
  50f937:	00 00 00 
  50f93a:	5b                   	pop    ebx
  50f93b:	e8 6e a7 07 00       	call   0x58a0ae
  50f940:	8b e5                	mov    esp,ebp
  50f942:	5d                   	pop    ebp
  50f943:	c3                   	ret
  50f944:	e8 99 a8 07 00       	call   0x58a1e2
  50f949:	cc                   	int3
  50f94a:	cc                   	int3
  50f94b:	cc                   	int3
  50f94c:	cc                   	int3
  50f94d:	cc                   	int3
  50f94e:	cc                   	int3
  50f94f:	cc                   	int3
