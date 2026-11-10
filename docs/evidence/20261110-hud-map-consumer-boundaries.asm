  4e284e:	cc                   	int3
  4e284f:	cc                   	int3
  4e2850:	55                   	push   ebp
  4e2851:	8b ec                	mov    ebp,esp
  4e2853:	53                   	push   ebx
  4e2854:	56                   	push   esi

  4e2ac2:	68 c0 68 5a 00       	push   0x5a68c0
  4e2ac7:	50                   	push   eax
  4e2ac8:	e8 03 e6 f1 ff       	call   0x4010d0
  4e2acd:	8b 15 60 b7 37 06    	mov    edx,DWORD PTR ds:0x637b760
  4e2ad3:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4e2ad9:	8b 0d 5c b7 37 06    	mov    ecx,DWORD PTR ds:0x637b75c

  4e2adf:	50                   	push   eax
  4e2ae0:	6a 01                	push   0x1
  4e2ae2:	e8 69 fd ff ff       	call   0x4e2850
  4e2ae7:	8b 0d 10 ca 36 06    	mov    ecx,DWORD PTR ds:0x636ca10
  4e2aed:	83 c4 18             	add    esp,0x18
  4e2af0:	85 c9                	test   ecx,ecx

  4e2bc0:	68 1c 69 5a 00       	push   0x5a691c
  4e2bc5:	50                   	push   eax
  4e2bc6:	e8 05 e5 f1 ff       	call   0x4010d0
  4e2bcb:	8b 15 14 ca 36 06    	mov    edx,DWORD PTR ds:0x636ca14
  4e2bd1:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4e2bd7:	8b 0d 10 ca 36 06    	mov    ecx,DWORD PTR ds:0x636ca10

  4e2bdd:	50                   	push   eax
  4e2bde:	ff b5 f4 fb ff ff    	push   DWORD PTR [ebp-0x40c]
  4e2be4:	e8 67 fc ff ff       	call   0x4e2850
  4e2be9:	83 c4 18             	add    esp,0x18
  4e2bec:	8b 1d 5c ca 36 06    	mov    ebx,DWORD PTR ds:0x636ca5c
  4e2bf2:	85 db                	test   ebx,ebx

  4e2cc0:	68 1c 69 5a 00       	push   0x5a691c
  4e2cc5:	50                   	push   eax
  4e2cc6:	e8 05 e4 f1 ff       	call   0x4010d0
  4e2ccb:	8b 15 60 ca 36 06    	mov    edx,DWORD PTR ds:0x636ca60
  4e2cd1:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4e2cd7:	8b 0d 5c ca 36 06    	mov    ecx,DWORD PTR ds:0x636ca5c

  4e2cdd:	50                   	push   eax
  4e2cde:	ff b5 f4 fb ff ff    	push   DWORD PTR [ebp-0x40c]
  4e2ce4:	e8 67 fb ff ff       	call   0x4e2850
  4e2ce9:	83 c4 18             	add    esp,0x18
  4e2cec:	b9 80 b9 37 06       	mov    ecx,0x637b980
  4e2cf1:	89 8d f0 fb ff ff    	mov    DWORD PTR [ebp-0x410],ecx

  4e2e20:	68 58 69 5a 00       	push   0x5a6958
  4e2e25:	50                   	push   eax
  4e2e26:	e8 a5 e2 f1 ff       	call   0x4010d0
  4e2e2b:	8d bd f8 fb ff ff    	lea    edi,[ebp-0x408]
  4e2e31:	83 c4 0c             	add    esp,0xc
  4e2e34:	4f                   	dec    edi

  4e2e5c:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  4e2e5e:	b9 04 00 00 00       	mov    ecx,0x4
  4e2e63:	e8 88 b5 fc ff       	call   0x4ae3f0
  4e2e68:	8b d0                	mov    edx,eax
  4e2e6a:	81 c4 68 05 00 00    	add    esp,0x568
  4e2e70:	8b f2                	mov    esi,edx

  4e2edb:	50                   	push   eax
  4e2edc:	6a 01                	push   0x1
  4e2ede:	e8 6d f9 ff ff       	call   0x4e2850
  4e2ee3:	8b 0d 38 3f 39 06    	mov    ecx,DWORD PTR ds:0x6393f38
  4e2ee9:	83 c4 08             	add    esp,0x8
  4e2eec:	85 c9                	test   ecx,ecx

  4e2fbc:	68 1c 69 5a 00       	push   0x5a691c
  4e2fc1:	50                   	push   eax
  4e2fc2:	e8 09 e1 f1 ff       	call   0x4010d0
  4e2fc7:	8b 15 3c 3f 39 06    	mov    edx,DWORD PTR ds:0x6393f3c
  4e2fcd:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4e2fd3:	8b 0d 38 3f 39 06    	mov    ecx,DWORD PTR ds:0x6393f38

  4e2fd9:	50                   	push   eax
  4e2fda:	ff b5 f4 fb ff ff    	push   DWORD PTR [ebp-0x40c]
  4e2fe0:	e8 6b f8 ff ff       	call   0x4e2850
  4e2fe5:	83 c4 18             	add    esp,0x18
  4e2fe8:	8b 8d f0 fb ff ff    	mov    ecx,DWORD PTR [ebp-0x410]
  4e2fee:	83 c1 04             	add    ecx,0x4

  4e41dd:	66 0f d6 45 90       	movq   QWORD PTR [ebp-0x70],xmm0
  4e41e2:	89 45 98             	mov    DWORD PTR [ebp-0x68],eax
  4e41e5:	e8 16 e1 07 00       	call   0x562300
  4e41ea:	ba 10 6b 5a 00       	mov    edx,0x5a6b10
  4e41ef:	33 c9                	xor    ecx,ecx
  4e41f1:	e8 0a e1 07 00       	call   0x562300

  4e41ea:	ba 10 6b 5a 00       	mov    edx,0x5a6b10
  4e41ef:	33 c9                	xor    ecx,ecx
  4e41f1:	e8 0a e1 07 00       	call   0x562300
  4e41f6:	ff 35 44 b6 5b 06    	push   DWORD PTR ds:0x65bb644
  4e41fc:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e4202:	ff d6                	call   esi

  4e4220:	6a 00                	push   0x0
  4e4222:	33 d2                	xor    edx,edx
  4e4224:	e8 97 24 03 00       	call   0x5166c0
  4e4229:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  4e422f:	ba 0a 00 00 00       	mov    edx,0xa
  4e4234:	6a 00                	push   0x0

  4e423e:	68 44 02 00 00       	push   0x244
  4e4243:	6a 64                	push   0x64
  4e4245:	e8 86 ad 02 00       	call   0x50efd0
  4e424a:	0f b6 85 d8 f5 ff ff 	movzx  eax,BYTE PTR [ebp-0xa28]
  4e4251:	83 c4 34             	add    esp,0x34
  4e4254:	83 c0 fe             	add    eax,0xfffffffe

  4e4408:	50                   	push   eax
  4e4409:	6a 1e                	push   0x1e
  4e440b:	e8 50 9e 02 00       	call   0x50e260
  4e4410:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  4e4416:	8d 85 44 f6 ff ff    	lea    eax,[ebp-0x9bc]
  4e441c:	6a 00                	push   0x0

  4e4429:	50                   	push   eax
  4e442a:	6a 2d                	push   0x2d
  4e442c:	e8 2f 9e 02 00       	call   0x50e260
  4e4431:	83 c4 48             	add    esp,0x48
  4e4434:	6a 00                	push   0x0
  4e4436:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc

  4e45f1:	68 80 6b 5a 00       	push   0x5a6b80
  4e45f6:	6a 47                	push   0x47
  4e45f8:	e8 63 9c 02 00       	call   0x50e260
  4e45fd:	6a 00                	push   0x0
  4e45ff:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e4605:	ff d6                	call   esi

  4e4a16:	68 58 02 00 00       	push   0x258
  4e4a1b:	6a 00                	push   0x0
  4e4a1d:	e8 9e 1c 03 00       	call   0x5166c0
  4e4a22:	6a 00                	push   0x0
  4e4a24:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e4a2a:	ff d6                	call   esi

  4e4d9d:	8d 56 06             	lea    edx,[esi+0x6]
  4e4da0:	33 c9                	xor    ecx,ecx
  4e4da2:	e8 59 d5 07 00       	call   0x562300
  4e4da7:	8d 96 06 04 00 00    	lea    edx,[esi+0x406]
  4e4dad:	8b ca                	mov    ecx,edx
  4e4daf:	8d 79 01             	lea    edi,[ecx+0x1]

  4e4dbb:	74 07                	je     0x4e4dc4
  4e4dbd:	33 c9                	xor    ecx,ecx
  4e4dbf:	e8 3c d5 07 00       	call   0x562300
  4e4dc4:	8d 96 06 08 00 00    	lea    edx,[esi+0x806]
  4e4dca:	8b ca                	mov    ecx,edx
  4e4dcc:	8d 79 01             	lea    edi,[ecx+0x1]

  4e4dd9:	74 07                	je     0x4e4de2
  4e4ddb:	33 c9                	xor    ecx,ecx
  4e4ddd:	e8 1e d5 07 00       	call   0x562300
  4e4de2:	8d 96 06 0c 00 00    	lea    edx,[esi+0xc06]
  4e4de8:	8b ca                	mov    ecx,edx
  4e4dea:	8d 79 01             	lea    edi,[ecx+0x1]

  4e4df9:	74 07                	je     0x4e4e02
  4e4dfb:	33 c9                	xor    ecx,ecx
  4e4dfd:	e8 fe d4 07 00       	call   0x562300
  4e4e02:	8b bd 2c ee ff ff    	mov    edi,DWORD PTR [ebp-0x11d4]
  4e4e08:	83 fb 32             	cmp    ebx,0x32
  4e4e0b:	b8 32 00 00 00       	mov    eax,0x32

  4e4f8e:	68 b0 6b 5a 00       	push   0x5a6bb0
  4e4f93:	50                   	push   eax
  4e4f94:	e8 37 c1 f1 ff       	call   0x4010d0
  4e4f99:	83 c4 0c             	add    esp,0xc
  4e4f9c:	8d 95 f8 f7 ff ff    	lea    edx,[ebp-0x808]
  4e4fa2:	33 c9                	xor    ecx,ecx

  4e4f9c:	8d 95 f8 f7 ff ff    	lea    edx,[ebp-0x808]
  4e4fa2:	33 c9                	xor    ecx,ecx
  4e4fa4:	e8 57 d3 07 00       	call   0x562300
  4e4fa9:	8d 8d f8 f7 ff ff    	lea    ecx,[ebp-0x808]
  4e4faf:	8d 51 01             	lea    edx,[ecx+0x1]
  4e4fb2:	8a 01                	mov    al,BYTE PTR [ecx]

  4e4fb5:	84 c0                	test   al,al
  4e4fb7:	75 f9                	jne    0x4e4fb2
  4e4fb9:	2b ca                	sub    ecx,edx
  4e4fbb:	c6 85 37 ee ff ff 01 	mov    BYTE PTR [ebp-0x11c9],0x1
  4e4fc2:	3b cb                	cmp    ecx,ebx
  4e4fc4:	c6 85 36 ee ff ff 01 	mov    BYTE PTR [ebp-0x11ca],0x1

  4e5057:	68 cc 6b 5a 00       	push   0x5a6bcc
  4e505c:	50                   	push   eax
  4e505d:	e8 6e c0 f1 ff       	call   0x4010d0
  4e5062:	83 c4 0c             	add    esp,0xc
  4e5065:	eb 37                	jmp    0x4e509e
  4e5067:	f3 0f 7e 05 c0 6b 5a 	movq   xmm0,QWORD PTR ds:0x5a6bc0

  4e50e1:	68 d8 6b 5a 00       	push   0x5a6bd8
  4e50e6:	50                   	push   eax
  4e50e7:	e8 e4 bf f1 ff       	call   0x4010d0
  4e50ec:	83 c4 10             	add    esp,0x10
  4e50ef:	8d 95 f8 f7 ff ff    	lea    edx,[ebp-0x808]
  4e50f5:	33 c9                	xor    ecx,ecx

  4e50ef:	8d 95 f8 f7 ff ff    	lea    edx,[ebp-0x808]
  4e50f5:	33 c9                	xor    ecx,ecx
  4e50f7:	e8 04 d2 07 00       	call   0x562300
  4e50fc:	8d 8d f8 f7 ff ff    	lea    ecx,[ebp-0x808]
  4e5102:	8d 51 01             	lea    edx,[ecx+0x1]
  4e5105:	8a 01                	mov    al,BYTE PTR [ecx]

  4e5108:	84 c0                	test   al,al
  4e510a:	75 f9                	jne    0x4e5105
  4e510c:	2b ca                	sub    ecx,edx
  4e510e:	ba 6c 41 59 00       	mov    edx,0x59416c
  4e5113:	3b cb                	cmp    ecx,ebx
  4e5115:	0f 47 d9             	cmova  ebx,ecx

  4e5173:	84 c0                	test   al,al
  4e5175:	75 f9                	jne    0x4e5170
  4e5177:	2b ca                	sub    ecx,edx
  4e5179:	8d 41 04             	lea    eax,[ecx+0x4]
  4e517c:	3b c3                	cmp    eax,ebx
  4e517e:	8d 8d ac ee ff ff    	lea    ecx,[ebp-0x1154]

  4e5195:	75 f9                	jne    0x4e5190
  4e5197:	8b b5 08 ee ff ff    	mov    esi,DWORD PTR [ebp-0x11f8]
  4e519d:	2b ca                	sub    ecx,edx
  4e519f:	8b bd 00 ee ff ff    	mov    edi,DWORD PTR [ebp-0x1200]
  4e51a5:	c6 85 36 ee ff ff 01 	mov    BYTE PTR [ebp-0x11ca],0x1
  4e51ac:	8d 41 04             	lea    eax,[ecx+0x4]

  4e534c:	68 cc 6b 5a 00       	push   0x5a6bcc
  4e5351:	50                   	push   eax
  4e5352:	e8 79 bd f1 ff       	call   0x4010d0
  4e5357:	83 c4 0c             	add    esp,0xc
  4e535a:	eb 37                	jmp    0x4e5393
  4e535c:	f3 0f 7e 05 c0 6b 5a 	movq   xmm0,QWORD PTR ds:0x5a6bc0

  4e53a9:	68 fc 6b 5a 00       	push   0x5a6bfc
  4e53ae:	50                   	push   eax
  4e53af:	e8 1c bd f1 ff       	call   0x4010d0
  4e53b4:	83 c4 0c             	add    esp,0xc
  4e53b7:	f6 87 00 2b 42 06 04 	test   BYTE PTR [edi+0x6422b00],0x4
  4e53be:	74 1b                	je     0x4e53db

  4e53cd:	68 18 6c 5a 00       	push   0x5a6c18
  4e53d2:	50                   	push   eax
  4e53d3:	e8 f8 bc f1 ff       	call   0x4010d0
  4e53d8:	83 c4 0c             	add    esp,0xc
  4e53db:	8d 8d f8 f7 ff ff    	lea    ecx,[ebp-0x808]
  4e53e1:	8d 51 01             	lea    edx,[ecx+0x1]

  4e53ef:	8d 95 f8 f7 ff ff    	lea    edx,[ebp-0x808]
  4e53f5:	33 c9                	xor    ecx,ecx
  4e53f7:	e8 04 cf 07 00       	call   0x562300
  4e53fc:	8d 8d f8 f7 ff ff    	lea    ecx,[ebp-0x808]
  4e5402:	8d 51 01             	lea    edx,[ecx+0x1]
  4e5405:	8a 01                	mov    al,BYTE PTR [ecx]

  4e5408:	84 c0                	test   al,al
  4e540a:	75 f9                	jne    0x4e5405
  4e540c:	2b ca                	sub    ecx,edx
  4e540e:	b0 01                	mov    al,0x1
  4e5410:	3b cb                	cmp    ecx,ebx
  4e5412:	88 85 37 ee ff ff    	mov    BYTE PTR [ebp-0x11c9],al

  4e54df:	50                   	push   eax
  4e54e0:	6a 01                	push   0x1
  4e54e2:	e8 e9 9a 02 00       	call   0x50efd0
  4e54e7:	83 c4 14             	add    esp,0x14
  4e54ea:	80 3d cb e3 17 02 00 	cmp    BYTE PTR ds:0x217e3cb,0x0
  4e54f1:	8d 70 0a             	lea    esi,[eax+0xa]

  4e5591:	6a 0a                	push   0xa
  4e5593:	8b cf                	mov    ecx,edi
  4e5595:	e8 36 9a 02 00       	call   0x50efd0
  4e559a:	83 c4 2c             	add    esp,0x2c
  4e559d:	80 3d cb e3 17 02 00 	cmp    BYTE PTR ds:0x217e3cb,0x0
  4e55a4:	0f 84 7b 02 00 00    	je     0x4e5825

  4e577f:	53                   	push   ebx
  4e5780:	56                   	push   esi
  4e5781:	e8 da 8a 02 00       	call   0x50e260
  4e5786:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4e578d:	00 
  4e578e:	8d 43 64             	lea    eax,[ebx+0x64]

  4e57a8:	03 c6                	add    eax,esi
  4e57aa:	50                   	push   eax
  4e57ab:	e8 b0 8a 02 00       	call   0x50e260
  4e57b0:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4e57b7:	00 
  4e57b8:	8b d6                	mov    edx,esi

  4e581a:	50                   	push   eax
  4e581b:	8b cf                	mov    ecx,edi
  4e581d:	e8 3e 8a 02 00       	call   0x50e260
  4e5822:	83 c4 10             	add    esp,0x10
  4e5825:	a1 44 b6 5b 06       	mov    eax,ds:0x65bb644
  4e582a:	85 c0                	test   eax,eax

  4f97b8:	eb 21                	jmp    0x4f97db
  4f97ba:	8b ce                	mov    ecx,esi
  4f97bc:	e8 ef 30 f7 ff       	call   0x46c8b0
  4f97c1:	8b d0                	mov    edx,eax
  4f97c3:	8b f0                	mov    esi,eax
  4f97c5:	8a 02                	mov    al,BYTE PTR [edx]

  4f9838:	eb 21                	jmp    0x4f985b
  4f983a:	8b ce                	mov    ecx,esi
  4f983c:	e8 6f 30 f7 ff       	call   0x46c8b0
  4f9841:	8b d0                	mov    edx,eax
  4f9843:	8b f0                	mov    esi,eax
  4f9845:	8a 02                	mov    al,BYTE PTR [edx]

  4f9864:	83 e1 03             	and    ecx,0x3
  4f9867:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
  4f9869:	8d 4c 24 20          	lea    ecx,[esp+0x20]
  4f986d:	8d 51 01             	lea    edx,[ecx+0x1]
  4f9870:	8a 01                	mov    al,BYTE PTR [ecx]
  4f9872:	41                   	inc    ecx

  4f98ed:	50                   	push   eax
  4f98ee:	8d 4a 1a             	lea    ecx,[edx+0x1a]
  4f98f1:	e8 aa 4c 01 00       	call   0x50e5a0
  4f98f6:	83 c4 0c             	add    esp,0xc
  4f98f9:	8b 8c 24 8c 00 00 00 	mov    ecx,DWORD PTR [esp+0x8c]
  4f9900:	5f                   	pop    edi

  5639f5:	81 fe a4 01 00 00    	cmp    esi,0x1a4
  5639fb:	74 1f                	je     0x563a1c
  5639fd:	ba 38 1c 6d 0a       	mov    edx,0xa6d1c38
  563a02:	89 35 a4 6a 6c 0a    	mov    DWORD PTR ds:0xa6c6aa4,esi
  563a08:	89 1d 3c 6a 6c 0a    	mov    DWORD PTR ds:0xa6c6a3c,ebx
  563a0e:	8b cf                	mov    ecx,edi

