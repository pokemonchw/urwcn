
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004f9ee2 <.text+0xf8ee2>:
  4f9ee2:	83 3d c4 6e 5e 00 00 	cmp    DWORD PTR ds:0x5e6ec4,0x0
  4f9ee9:	75 3c                	jne    0x4f9f27
  4f9eeb:	8b 0d 7c b1 72 0a    	mov    ecx,DWORD PTR ds:0xa72b17c
  4f9ef1:	e8 8a 60 06 00       	call   0x55ff80
  4f9ef6:	51                   	push   ecx
  4f9ef7:	6a 0d                	push   0xd
  4f9ef9:	6a 69                	push   0x69
  4f9efb:	ba f0 00 00 00       	mov    edx,0xf0
  4f9f00:	c7 05 b4 1c 5c 0a 00 	mov    DWORD PTR ds:0xa5c1cb4,0x0
  4f9f07:	00 00 00 
  4f9f0a:	b9 a7 02 00 00       	mov    ecx,0x2a7
  4f9f0f:	c7 05 3c bb 5b 06 00 	mov    DWORD PTR ds:0x65bbb3c,0x0
  4f9f16:	00 00 00 
  4f9f19:	8b f0                	mov    esi,eax
  4f9f1b:	e8 60 75 01 00       	call   0x511480
  4f9f20:	ba f3 00 00 00       	mov    edx,0xf3
  4f9f25:	eb 3a                	jmp    0x4f9f61
  4f9f27:	8b 0d 7c b1 72 0a    	mov    ecx,DWORD PTR ds:0xa72b17c
  4f9f2d:	e8 4e 60 06 00       	call   0x55ff80
  4f9f32:	51                   	push   ecx
  4f9f33:	6a 0d                	push   0xd
  4f9f35:	6a 69                	push   0x69
  4f9f37:	ba d1 00 00 00       	mov    edx,0xd1
  4f9f3c:	c7 05 b4 1c 5c 0a 00 	mov    DWORD PTR ds:0xa5c1cb4,0x0
  4f9f43:	00 00 00 
  4f9f46:	b9 a7 02 00 00       	mov    ecx,0x2a7
  4f9f4b:	c7 05 3c bb 5b 06 00 	mov    DWORD PTR ds:0x65bbb3c,0x0
  4f9f52:	00 00 00 
  4f9f55:	8b f0                	mov    esi,eax
  4f9f57:	e8 24 75 01 00       	call   0x511480
  4f9f5c:	ba d4 00 00 00       	mov    edx,0xd4
  4f9f61:	83 c4 0c             	add    esp,0xc
  4f9f64:	b9 aa 02 00 00       	mov    ecx,0x2aa
  4f9f69:	6a 00                	push   0x0
  4f9f6b:	ff 74 24 2c          	push   DWORD PTR [esp+0x2c]
  4f9f6f:	56                   	push   esi
  4f9f70:	e8 2b 46 01 00       	call   0x50e5a0
  4f9f75:	83 c4 0c             	add    esp,0xc
  4f9f78:	8d 54 24 28          	lea    edx,[esp+0x28]
  4f9f7c:	32 c9                	xor    cl,cl
  4f9f7e:	e8 cd 54 06 00       	call   0x55f450
  4f9f83:	8d 54 24 38          	lea    edx,[esp+0x38]
  4f9f87:	2b d0                	sub    edx,eax
  4f9f89:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  4f9f90:	8a 08                	mov    cl,BYTE PTR [eax]
  4f9f92:	8d 40 01             	lea    eax,[eax+0x1]
  4f9f95:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  4f9f99:	84 c9                	test   cl,cl
  4f9f9b:	75 f3                	jne    0x4f9f90
  4f9f9d:	83 3d c4 6e 5e 00 00 	cmp    DWORD PTR ds:0x5e6ec4,0x0
  4f9fa4:	bb ff 00 00 00       	mov    ebx,0xff
  4f9fa9:	8b 44 24 28          	mov    eax,DWORD PTR [esp+0x28]
  4f9fad:	0f b6 d0             	movzx  edx,al
  4f9fb0:	0f b6 cc             	movzx  ecx,ah
  4f9fb3:	0f b6 44 24 2a       	movzx  eax,BYTE PTR [esp+0x2a]
  4f9fb8:	75 53                	jne    0x4fa00d
  4f9fba:	3b d3                	cmp    edx,ebx
  4f9fbc:	0f 4f d3             	cmovg  edx,ebx
  4f9fbf:	3b cb                	cmp    ecx,ebx
  4f9fc1:	0f 4f cb             	cmovg  ecx,ebx
  4f9fc4:	3b c3                	cmp    eax,ebx
  4f9fc6:	0f 4f c3             	cmovg  eax,ebx
  4f9fc9:	50                   	push   eax
  4f9fca:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4f9fcf:	51                   	push   ecx
  4f9fd0:	52                   	push   edx
  4f9fd1:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4f9fd4:	ff d7                	call   edi
  4f9fd6:	83 c4 0c             	add    esp,0xc
  4f9fd9:	c7 05 b4 1c 5c 0a 00 	mov    DWORD PTR ds:0xa5c1cb4,0x0
  4f9fe0:	00 00 00 
  4f9fe3:	8d 53 0d             	lea    edx,[ebx+0xd]
  4f9fe6:	c7 05 3c bb 5b 06 00 	mov    DWORD PTR ds:0x65bbb3c,0x0
  4f9fed:	00 00 00 
  4f9ff0:	b9 71 02 00 00       	mov    ecx,0x271
  4f9ff5:	8b f0                	mov    esi,eax
  4f9ff7:	6a 0d                	push   0xd
  4f9ff9:	68 a0 00 00 00       	push   0xa0
  4f9ffe:	e8 7d 74 01 00       	call   0x511480
  4fa003:	8d 53 10             	lea    edx,[ebx+0x10]
  4fa006:	b9 74 02 00 00       	mov    ecx,0x274
  4fa00b:	eb 5c                	jmp    0x4fa069
  4fa00d:	81 fa ff 00 00 00    	cmp    edx,0xff
  4fa013:	0f 4f d3             	cmovg  edx,ebx
  4fa016:	3b cb                	cmp    ecx,ebx
  4fa018:	0f 4f cb             	cmovg  ecx,ebx
  4fa01b:	3d ff 00 00 00       	cmp    eax,0xff
  4fa020:	0f 4f c3             	cmovg  eax,ebx
  4fa023:	50                   	push   eax
  4fa024:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fa029:	51                   	push   ecx
  4fa02a:	52                   	push   edx
  4fa02b:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fa02e:	ff d7                	call   edi
  4fa030:	83 c4 0c             	add    esp,0xc
  4fa033:	c7 05 b4 1c 5c 0a 00 	mov    DWORD PTR ds:0xa5c1cb4,0x0
  4fa03a:	00 00 00 
  4fa03d:	ba e2 00 00 00       	mov    edx,0xe2
  4fa042:	c7 05 3c bb 5b 06 00 	mov    DWORD PTR ds:0x65bbb3c,0x0
  4fa049:	00 00 00 
  4fa04c:	b9 38 02 00 00       	mov    ecx,0x238
  4fa051:	8b f0                	mov    esi,eax
  4fa053:	6a 0d                	push   0xd
  4fa055:	68 a0 00 00 00       	push   0xa0
  4fa05a:	e8 21 74 01 00       	call   0x511480
  4fa05f:	ba e5 00 00 00       	mov    edx,0xe5
  4fa064:	b9 3b 02 00 00       	mov    ecx,0x23b
  4fa069:	83 c4 0c             	add    esp,0xc
  4fa06c:	8d 44 24 38          	lea    eax,[esp+0x38]
  4fa070:	6a 00                	push   0x0
  4fa072:	56                   	push   esi
  4fa073:	50                   	push   eax
  4fa074:	e8 27 45 01 00       	call   0x50e5a0
  4fa079:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fa07e:	83 c4 0c             	add    esp,0xc
  4fa081:	83 3d c4 6e 5e 00 00 	cmp    DWORD PTR ds:0x5e6ec4,0x0
  4fa088:	68 ab 00 00 00       	push   0xab
  4fa08d:	68 ab 00 00 00       	push   0xab
  4fa092:	68 ab 00 00 00       	push   0xab
  4fa097:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fa09a:	0f 85 ee 00 00 00    	jne    0x4fa18e
  4fa0a0:	ff d7                	call   edi
  4fa0a2:	8b 15 d8 b0 72 0a    	mov    edx,DWORD PTR ds:0xa72b0d8
  4fa0a8:	83 c4 10             	add    esp,0x10
  4fa0ab:	8b f8                	mov    edi,eax
  4fa0ad:	81 fa f4 01 00 00    	cmp    edx,0x1f4
  4fa0b3:	7d 0b                	jge    0x4fa0c0
  4fa0b5:	8b 35 38 e9 58 00    	mov    esi,DWORD PTR ds:0x58e938
  4fa0bb:	e9 94 00 00 00       	jmp    0x4fa154
  4fa0c0:	33 c9                	xor    ecx,ecx
  4fa0c2:	81 fa 14 05 00 00    	cmp    edx,0x514
  4fa0c8:	0f 9c c1             	setl   cl
  4fa0cb:	33 c0                	xor    eax,eax
  4fa0cd:	81 fa e8 03 00 00    	cmp    edx,0x3e8
  4fa0d3:	0f 9d c0             	setge  al
  4fa0d6:	85 c8                	test   eax,ecx
  4fa0d8:	74 08                	je     0x4fa0e2
  4fa0da:	8b 35 40 e9 58 00    	mov    esi,DWORD PTR ds:0x58e940
  4fa0e0:	eb 72                	jmp    0x4fa154
  4fa0e2:	33 c9                	xor    ecx,ecx
  4fa0e4:	81 fa 40 06 00 00    	cmp    edx,0x640
  4fa0ea:	0f 9c c1             	setl   cl
  4fa0ed:	33 c0                	xor    eax,eax
  4fa0ef:	81 fa 14 05 00 00    	cmp    edx,0x514
  4fa0f5:	0f 9d c0             	setge  al
  4fa0f8:	85 c8                	test   eax,ecx
  4fa0fa:	74 08                	je     0x4fa104
  4fa0fc:	8b 35 44 e9 58 00    	mov    esi,DWORD PTR ds:0x58e944
  4fa102:	eb 50                	jmp    0x4fa154
  4fa104:	33 c9                	xor    ecx,ecx
  4fa106:	81 fa 08 07 00 00    	cmp    edx,0x708
  4fa10c:	0f 9c c1             	setl   cl
  4fa10f:	33 c0                	xor    eax,eax
  4fa111:	81 fa 40 06 00 00    	cmp    edx,0x640
  4fa117:	0f 9d c0             	setge  al
  4fa11a:	85 c8                	test   eax,ecx
  4fa11c:	74 08                	je     0x4fa126
  4fa11e:	8b 35 48 e9 58 00    	mov    esi,DWORD PTR ds:0x58e948
  4fa124:	eb 2e                	jmp    0x4fa154
  4fa126:	81 fa 08 07 00 00    	cmp    edx,0x708
  4fa12c:	7c 10                	jl     0x4fa13e
  4fa12e:	81 fa d0 07 00 00    	cmp    edx,0x7d0
  4fa134:	7d 10                	jge    0x4fa146
  4fa136:	8b 35 4c e9 58 00    	mov    esi,DWORD PTR ds:0x58e94c
  4fa13c:	eb 16                	jmp    0x4fa154
  4fa13e:	81 fa d0 07 00 00    	cmp    edx,0x7d0
  4fa144:	7c 08                	jl     0x4fa14e
  4fa146:	8b 35 50 e9 58 00    	mov    esi,DWORD PTR ds:0x58e950
  4fa14c:	eb 06                	jmp    0x4fa154
  4fa14e:	8b 35 3c e9 58 00    	mov    esi,DWORD PTR ds:0x58e93c
  4fa154:	51                   	push   ecx
  4fa155:	6a 0d                	push   0xd
  4fa157:	68 a0 00 00 00       	push   0xa0
  4fa15c:	ba 1b 01 00 00       	mov    edx,0x11b
  4fa161:	c7 05 b4 1c 5c 0a 00 	mov    DWORD PTR ds:0xa5c1cb4,0x0
  4fa168:	00 00 00 
  4fa16b:	b9 71 02 00 00       	mov    ecx,0x271
  4fa170:	c7 05 3c bb 5b 06 00 	mov    DWORD PTR ds:0x65bbb3c,0x0
  4fa177:	00 00 00 
  4fa17a:	e8 01 73 01 00       	call   0x511480
  4fa17f:	ba 1e 01 00 00       	mov    edx,0x11e
  4fa184:	b9 74 02 00 00       	mov    ecx,0x274
  4fa189:	e9 e9 00 00 00       	jmp    0x4fa277
  4fa18e:	ff d7                	call   edi
  4fa190:	8b 15 d8 b0 72 0a    	mov    edx,DWORD PTR ds:0xa72b0d8
  4fa196:	83 c4 10             	add    esp,0x10
  4fa199:	8b f8                	mov    edi,eax
  4fa19b:	81 fa f4 01 00 00    	cmp    edx,0x1f4
  4fa1a1:	7d 0b                	jge    0x4fa1ae
  4fa1a3:	8b 35 38 e9 58 00    	mov    esi,DWORD PTR ds:0x58e938
  4fa1a9:	e9 94 00 00 00       	jmp    0x4fa242
  4fa1ae:	33 c9                	xor    ecx,ecx
  4fa1b0:	81 fa 14 05 00 00    	cmp    edx,0x514
  4fa1b6:	0f 9c c1             	setl   cl
  4fa1b9:	33 c0                	xor    eax,eax
  4fa1bb:	81 fa e8 03 00 00    	cmp    edx,0x3e8
  4fa1c1:	0f 9d c0             	setge  al
  4fa1c4:	85 c8                	test   eax,ecx
  4fa1c6:	74 08                	je     0x4fa1d0
  4fa1c8:	8b 35 40 e9 58 00    	mov    esi,DWORD PTR ds:0x58e940
  4fa1ce:	eb 72                	jmp    0x4fa242
  4fa1d0:	33 c9                	xor    ecx,ecx
  4fa1d2:	81 fa 40 06 00 00    	cmp    edx,0x640
  4fa1d8:	0f 9c c1             	setl   cl
  4fa1db:	33 c0                	xor    eax,eax
  4fa1dd:	81 fa 14 05 00 00    	cmp    edx,0x514
  4fa1e3:	0f 9d c0             	setge  al
  4fa1e6:	85 c8                	test   eax,ecx
  4fa1e8:	74 08                	je     0x4fa1f2
  4fa1ea:	8b 35 44 e9 58 00    	mov    esi,DWORD PTR ds:0x58e944
  4fa1f0:	eb 50                	jmp    0x4fa242
  4fa1f2:	33 c9                	xor    ecx,ecx
  4fa1f4:	81 fa 08 07 00 00    	cmp    edx,0x708
  4fa1fa:	0f 9c c1             	setl   cl
  4fa1fd:	33 c0                	xor    eax,eax
  4fa1ff:	81 fa 40 06 00 00    	cmp    edx,0x640
  4fa205:	0f 9d c0             	setge  al
  4fa208:	85 c8                	test   eax,ecx
  4fa20a:	74 08                	je     0x4fa214
  4fa20c:	8b 35 48 e9 58 00    	mov    esi,DWORD PTR ds:0x58e948
  4fa212:	eb 2e                	jmp    0x4fa242
  4fa214:	81 fa 08 07 00 00    	cmp    edx,0x708
  4fa21a:	7c 10                	jl     0x4fa22c
  4fa21c:	81 fa d0 07 00 00    	cmp    edx,0x7d0
  4fa222:	7d 10                	jge    0x4fa234
  4fa224:	8b 35 4c e9 58 00    	mov    esi,DWORD PTR ds:0x58e94c
  4fa22a:	eb 16                	jmp    0x4fa242
  4fa22c:	81 fa d0 07 00 00    	cmp    edx,0x7d0
  4fa232:	7c 08                	jl     0x4fa23c
  4fa234:	8b 35 50 e9 58 00    	mov    esi,DWORD PTR ds:0x58e950
  4fa23a:	eb 06                	jmp    0x4fa242
  4fa23c:	8b 35 3c e9 58 00    	mov    esi,DWORD PTR ds:0x58e93c
  4fa242:	51                   	push   ecx
  4fa243:	6a 0d                	push   0xd
  4fa245:	68 a0 00 00 00       	push   0xa0
  4fa24a:	ba f0 00 00 00       	mov    edx,0xf0
  4fa24f:	c7 05 b4 1c 5c 0a 00 	mov    DWORD PTR ds:0xa5c1cb4,0x0
  4fa256:	00 00 00 
  4fa259:	b9 38 02 00 00       	mov    ecx,0x238
  4fa25e:	c7 05 3c bb 5b 06 00 	mov    DWORD PTR ds:0x65bbb3c,0x0
  4fa265:	00 00 00 
  4fa268:	e8 13 72 01 00       	call   0x511480
  4fa26d:	ba f3 00 00 00       	mov    edx,0xf3
  4fa272:	b9 3b 02 00 00       	mov    ecx,0x23b
  4fa277:	83 c4 0c             	add    esp,0xc
  4fa27a:	6a 00                	push   0x0
  4fa27c:	57                   	push   edi
  4fa27d:	56                   	push   esi
  4fa27e:	e8 1d 43 01 00       	call   0x50e5a0

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

00511480 <.text+0x110480>:
  511480:	55                   	push   ebp
  511481:	8b ec                	mov    ebp,esp
  511483:	83 ec 20             	sub    esp,0x20
  511486:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  51148b:	33 c5                	xor    eax,ebp
  51148d:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  511490:	a1 ec bc 5b 06       	mov    eax,ds:0x65bbcec
  511495:	53                   	push   ebx
  511496:	56                   	push   esi
  511497:	8b 75 08             	mov    esi,DWORD PTR [ebp+0x8]
  51149a:	8b da                	mov    ebx,edx
  51149c:	57                   	push   edi
  51149d:	8b f9                	mov    edi,ecx
  51149f:	89 5d e4             	mov    DWORD PTR [ebp-0x1c],ebx
  5114a2:	50                   	push   eax
  5114a3:	4e                   	dec    esi
  5114a4:	89 7d e0             	mov    DWORD PTR [ebp-0x20],edi
  5114a7:	03 f7                	add    esi,edi
  5114a9:	a3 68 10 61 0a       	mov    ds:0xa611068,eax
  5114ae:	53                   	push   ebx
  5114af:	56                   	push   esi
  5114b0:	e8 8b 2e 00 00       	call   0x514340
  5114b5:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
  5114b8:	83 c4 0c             	add    esp,0xc
  5114bb:	8b 55 e4             	mov    edx,DWORD PTR [ebp-0x1c]
  5114be:	48                   	dec    eax
  5114bf:	03 d8                	add    ebx,eax
  5114c1:	8b cf                	mov    ecx,edi
  5114c3:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  5114c9:	53                   	push   ebx
  5114ca:	57                   	push   edi
  5114cb:	e8 70 2e 00 00       	call   0x514340
  5114d0:	a1 bc 0e 5c 0a       	mov    eax,ds:0xa5c0ebc
  5114d5:	83 c4 0c             	add    esp,0xc
  5114d8:	47                   	inc    edi
  5114d9:	a3 68 10 61 0a       	mov    ds:0xa611068,eax
  5114de:	8b d3                	mov    edx,ebx
  5114e0:	8b cf                	mov    ecx,edi
  5114e2:	50                   	push   eax
  5114e3:	53                   	push   ebx
  5114e4:	56                   	push   esi
  5114e5:	e8 56 2e 00 00       	call   0x514340
  5114ea:	8b 75 e4             	mov    esi,DWORD PTR [ebp-0x1c]
  5114ed:	83 c4 0c             	add    esp,0xc
  5114f0:	8b 55 e0             	mov    edx,DWORD PTR [ebp-0x20]
  5114f3:	46                   	inc    esi
  5114f4:	8b 4d 08             	mov    ecx,DWORD PTR [ebp+0x8]
  5114f7:	4a                   	dec    edx
  5114f8:	03 ca                	add    ecx,edx
  5114fa:	8b d3                	mov    edx,ebx
  5114fc:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  511502:	56                   	push   esi
  511503:	51                   	push   ecx
  511504:	e8 37 2e 00 00       	call   0x514340
  511509:	8b 4d e0             	mov    ecx,DWORD PTR [ebp-0x20]
  51150c:	83 c4 0c             	add    esp,0xc
  51150f:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
  511512:	2b cf                	sub    ecx,edi
  511514:	48                   	dec    eax
  511515:	89 7d e8             	mov    DWORD PTR [ebp-0x18],edi
  511518:	03 c1                	add    eax,ecx
  51151a:	89 75 ec             	mov    DWORD PTR [ebp-0x14],esi
  51151d:	8b 4d e4             	mov    ecx,DWORD PTR [ebp-0x1c]
  511520:	89 45 f0             	mov    DWORD PTR [ebp-0x10],eax
  511523:	2b ce                	sub    ecx,esi
  511525:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
  511528:	48                   	dec    eax
  511529:	03 c1                	add    eax,ecx
  51152b:	89 45 f4             	mov    DWORD PTR [ebp-0xc],eax
  51152e:	8d 45 e8             	lea    eax,[ebp-0x18]
  511531:	6a 00                	push   0x0
  511533:	50                   	push   eax
  511534:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  51153a:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  511540:	8b 4d f8             	mov    ecx,DWORD PTR [ebp-0x8]
  511543:	83 c4 0c             	add    esp,0xc
  511546:	33 cd                	xor    ecx,ebp
  511548:	5f                   	pop    edi
  511549:	5e                   	pop    esi
  51154a:	5b                   	pop    ebx
  51154b:	e8 5e 8b 07 00       	call   0x58a0ae
  511550:	8b e5                	mov    esp,ebp
  511552:	5d                   	pop    ebp
  511553:	c3                   	ret
