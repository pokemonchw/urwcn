  54a6fc:	3b d6                	cmp    edx,esi
  54a6fe:	74 e6                	je     0x54a6e6
  54a700:	0f 10 05 74 87 5b 00 	movups xmm0,XMMWORD PTR ds:0x5b8774
  54a707:	8b 85 e0 f7 ff ff    	mov    eax,DWORD PTR [ebp-0x820]
  54a70d:	8b b5 ec f7 ff ff    	mov    esi,DWORD PTR [ebp-0x814]
  54a713:	48                   	dec    eax
  54a714:	8b 9d f0 f7 ff ff    	mov    ebx,DWORD PTR [ebp-0x810]
  54a71a:	03 c2                	add    eax,edx
  54a71c:	51                   	push   ecx
  54a71d:	0f 11 05 c8 e3 81 0a 	movups XMMWORD PTR ds:0xa81e3c8,xmm0
  54a724:	50                   	push   eax
  54a725:	0f 10 05 84 87 5b 00 	movups xmm0,XMMWORD PTR ds:0x5b8784
  54a72c:	8b d6                	mov    edx,esi
  54a72e:	8b cb                	mov    ecx,ebx
  54a730:	ff 35 c0 e3 81 0a    	push   DWORD PTR ds:0xa81e3c0
  54a736:	a3 c4 e3 81 0a       	mov    ds:0xa81e3c4,eax
  54a73b:	c6 05 08 e4 81 0a 01 	mov    BYTE PTR ds:0xa81e408,0x1
  54a742:	0f 11 05 d8 e3 81 0a 	movups XMMWORD PTR ds:0xa81e3d8,xmm0
  54a749:	e8 82 20 f5 ff       	call   0x49c7d0

  54d067:	83 ff 0a             	cmp    edi,0xa
  54d06a:	0f 44 f1             	cmove  esi,ecx
  54d06d:	3b c6                	cmp    eax,esi
  54d06f:	74 e2                	je     0x54d053
  54d071:	0f 10 05 18 d4 5b 00 	movups xmm0,XMMWORD PTR ds:0x5bd418
  54d078:	8b 8d 88 f3 ff ff    	mov    ecx,DWORD PTR [ebp-0xc78]
  54d07e:	be 48 d4 5b 00       	mov    esi,0x5bd448
  54d083:	8b 95 84 f3 ff ff    	mov    edx,DWORD PTR [ebp-0xc7c]
  54d089:	83 c1 f8             	add    ecx,0xfffffff8
  54d08c:	0f 11 05 a8 91 8c 0a 	movups XMMWORD PTR ds:0xa8c91a8,xmm0
  54d093:	03 c1                	add    eax,ecx
  54d095:	c6 05 e8 91 8c 0a 00 	mov    BYTE PTR ds:0xa8c91e8,0x0
  54d09c:	0f 10 05 28 d4 5b 00 	movups xmm0,XMMWORD PTR ds:0x5bd428
  54d0a3:	a3 a4 91 8c 0a       	mov    ds:0xa8c91a4,eax
  54d0a8:	b9 17 00 00 00       	mov    ecx,0x17
  54d0ad:	a0 40 d4 5b 00       	mov    al,ds:0x5bd440
  54d0b2:	bf 00 cb 8c 0a       	mov    edi,0xa8ccb00
  54d0b7:	0f 11 05 b8 91 8c 0a 	movups XMMWORD PTR ds:0xa8c91b8,xmm0
  54d0be:	a2 d0 91 8c 0a       	mov    ds:0xa8c91d0,al

  54e1ff:	3b c6                	cmp    eax,esi
  54e201:	74 e2                	je     0x54e1e5
  54e203:	8b 8d 54 ec ff ff    	mov    ecx,DWORD PTR [ebp-0x13ac]
  54e209:	0f 10 05 1c e0 5b 00 	movups xmm0,XMMWORD PTR ds:0x5be01c
  54e210:	83 c1 f8             	add    ecx,0xfffffff8
  54e213:	c6 05 08 e4 81 0a 00 	mov    BYTE PTR ds:0xa81e408,0x0
  54e21a:	03 c8                	add    ecx,eax
  54e21c:	a0 3c e0 5b 00       	mov    al,ds:0x5be03c
  54e221:	6a 03                	push   0x3
  54e223:	0f 11 05 c8 e3 81 0a 	movups XMMWORD PTR ds:0xa81e3c8,xmm0
  54e22a:	51                   	push   ecx
  54e22b:	0f 10 05 2c e0 5b 00 	movups xmm0,XMMWORD PTR ds:0x5be02c
  54e232:	89 0d c4 e3 81 0a    	mov    DWORD PTR ds:0xa81e3c4,ecx
  54e238:	ff 35 c0 e3 81 0a    	push   DWORD PTR ds:0xa81e3c0
  54e23e:	0f 11 05 d8 e3 81 0a 	movups XMMWORD PTR ds:0xa81e3d8,xmm0
  54e245:	a2 e8 e3 81 0a       	mov    ds:0xa81e3e8,al
  54e24a:	e8 f1 e8 f4 ff       	call   0x49cb40
  54e24f:	8b f0                	mov    esi,eax
  54e251:	e8 ba e8 f4 ff       	call   0x49cb10

  54f1e8:	89 95 a4 f5 ff ff    	mov    DWORD PTR [ebp-0xa5c],edx
  54f1ee:	83 c4 14             	add    esp,0x14
  54f1f1:	89 8d a0 f5 ff ff    	mov    DWORD PTR [ebp-0xa60],ecx
  54f1f7:	85 c9                	test   ecx,ecx
  54f1f9:	0f 84 54 ff ff ff    	je     0x54f153
  54f1ff:	0f 10 05 80 ef 5b 00 	movups xmm0,XMMWORD PTR ds:0x5bef80
  54f206:	a1 a8 ef 5b 00       	mov    eax,ds:0x5befa8
  54f20b:	a3 f0 e3 81 0a       	mov    ds:0xa81e3f0,eax
  54f210:	66 a1 ac ef 5b 00    	mov    ax,ds:0x5befac
  54f216:	0f 11 05 c8 e3 81 0a 	movups XMMWORD PTR ds:0xa81e3c8,xmm0
  54f21d:	6a 01                	push   0x1
  54f21f:	0f 10 05 90 ef 5b 00 	movups xmm0,XMMWORD PTR ds:0x5bef90
  54f226:	52                   	push   edx
  54f227:	66 a3 f4 e3 81 0a    	mov    ds:0xa81e3f4,ax
  54f22d:	a0 ae ef 5b 00       	mov    al,ds:0x5befae
  54f232:	0f 11 05 d8 e3 81 0a 	movups XMMWORD PTR ds:0xa81e3d8,xmm0
  54f239:	89 0d c0 e3 81 0a    	mov    DWORD PTR ds:0xa81e3c0,ecx
  54f23f:	f3 0f 7e 05 a0 ef 5b 	movq   xmm0,QWORD PTR ds:0x5befa0
  54f246:	00 

  55526f:	e8 9c 97 ed ff       	call   0x42ea10
  555274:	83 c4 08             	add    esp,0x8
  555277:	8d 45 8c             	lea    eax,[ebp-0x74]
  55527a:	89 1d 80 83 8d 0a    	mov    DWORD PTR ds:0xa8d8380,ebx
  555280:	50                   	push   eax
  555281:	68 50 94 5c 00       	push   0x5c9450
  555286:	68 88 83 8d 0a       	push   0xa8d8388
  55528b:	89 35 84 83 8d 0a    	mov    DWORD PTR ds:0xa8d8384,esi
  555291:	c6 05 c8 83 8d 0a 01 	mov    BYTE PTR ds:0xa8d83c8,0x1
  555298:	e8 33 be ea ff       	call   0x4010d0
  55529d:	8b 95 c8 fa ff ff    	mov    edx,DWORD PTR [ebp-0x538]
  5552a3:	83 c4 0c             	add    esp,0xc
  5552a6:	8b cf                	mov    ecx,edi
  5552a8:	6a 01                	push   0x1
  5552aa:	ff 35 84 83 8d 0a    	push   DWORD PTR ds:0xa8d8384
  5552b0:	ff 35 80 83 8d 0a    	push   DWORD PTR ds:0xa8d8380
  5552b6:	e8 15 75 f4 ff       	call   0x49c7d0
  5552bb:	8d 95 cc fa ff ff    	lea    edx,[ebp-0x534]
  5552c1:	83 c4 0c             	add    esp,0xc

