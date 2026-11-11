
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

00546f0f <.text+0x145f0f>:
  546f0f:	69 35 30 06 62 0a 68 	imul   esi,DWORD PTR ds:0xa620630,0x568
  546f16:	05 00 00 
  546f19:	b9 5a 01 00 00       	mov    ecx,0x15a
  546f1e:	bf 98 0e 15 06       	mov    edi,0x6150e98
  546f23:	c7 05 34 06 62 0a 00 	mov    DWORD PTR ds:0xa620634,0x0
  546f2a:	00 00 00 
  546f2d:	81 c6 00 14 15 06    	add    esi,0x6151400
  546f33:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  546f35:	e8 26 40 fc ff       	call   0x50af60
  546f3a:	e8 41 42 fc ff       	call   0x50b180
  546f3f:	8b 7c 24 14          	mov    edi,DWORD PTR [esp+0x14]
  546f43:	a1 5c ba 5b 06       	mov    eax,ds:0x65bba5c
  546f48:	a3 b0 1c 5c 0a       	mov    ds:0xa5c1cb0,eax
  546f4d:	c7 05 5c ba 5b 06 00 	mov    DWORD PTR ds:0x65bba5c,0x0
  546f54:	00 00 00 
  546f57:	e8 64 d3 fe ff       	call   0x5342c0
  546f5c:	a1 b0 1c 5c 0a       	mov    eax,ds:0xa5c1cb0
  546f61:	ba f4 69 5b 00       	mov    edx,0x5b69f4
  546f66:	6a 06                	push   0x6
  546f68:	68 96 00 00 00       	push   0x96
  546f6d:	68 ff 00 00 00       	push   0xff
  546f72:	6a 32                	push   0x32
  546f74:	68 08 02 00 00       	push   0x208
  546f79:	33 c9                	xor    ecx,ecx
  546f7b:	a3 5c ba 5b 06       	mov    ds:0x65bba5c,eax
  546f80:	e8 0b 88 f8 ff       	call   0x4cf790
  546f85:	83 c4 14             	add    esp,0x14
  546f88:	6a 01                	push   0x1
  546f8a:	6a 00                	push   0x0
  546f8c:	68 16 c6 58 00       	push   0x58c616
  546f91:	e8 7a 4d fc ff       	call   0x50bd10
  546f96:	8b c8                	mov    ecx,eax
  546f98:	e8 83 87 f8 ff       	call   0x4cf720
  546f9d:	83 c4 0c             	add    esp,0xc
  546fa0:	ba 00 6a 5b 00       	mov    edx,0x5b6a00
  546fa5:	b9 47 00 00 00       	mov    ecx,0x47
  546faa:	e8 e1 89 f8 ff       	call   0x4cf990
  546faf:	ba 08 6a 5b 00       	mov    edx,0x5b6a08
  546fb4:	b9 41 00 00 00       	mov    ecx,0x41
  546fb9:	e8 d2 89 f8 ff       	call   0x4cf990
  546fbe:	ba 20 6a 5b 00       	mov    edx,0x5b6a20
  546fc3:	b9 43 00 00 00       	mov    ecx,0x43
  546fc8:	e8 c3 89 f8 ff       	call   0x4cf990
  546fcd:	ba 2c 6a 5b 00       	mov    edx,0x5b6a2c
  546fd2:	b9 48 00 00 00       	mov    ecx,0x48
  546fd7:	e8 b4 89 f8 ff       	call   0x4cf990
  546fdc:	ba 40 6a 5b 00       	mov    edx,0x5b6a40
  546fe1:	b9 44 00 00 00       	mov    ecx,0x44
  546fe6:	e8 a5 89 f8 ff       	call   0x4cf990
  546feb:	ba 54 6a 5b 00       	mov    edx,0x5b6a54
  546ff0:	b9 54 00 00 00       	mov    ecx,0x54
  546ff5:	e8 96 89 f8 ff       	call   0x4cf990
  546ffa:	6a 01                	push   0x1
  546ffc:	e8 3f 5b f5 ff       	call   0x49cb40
  547001:	8b f0                	mov    esi,eax
  547003:	e8 08 5b f5 ff       	call   0x49cb10
  547008:	8b d6                	mov    edx,esi
  54700a:	8b c8                	mov    ecx,eax
  54700c:	e8 1f ef f4 ff       	call   0x495f30
  547011:	83 c4 04             	add    esp,0x4
  547014:	85 c0                	test   eax,eax
  547016:	74 18                	je     0x547030
  547018:	8b cb                	mov    ecx,ebx
  54701a:	e8 21 32 f6 ff       	call   0x4aa240
  54701f:	85 c0                	test   eax,eax
  547021:	75 0d                	jne    0x547030
  547023:	ba 64 6a 5b 00       	mov    edx,0x5b6a64
  547028:	8d 48 42             	lea    ecx,[eax+0x42]
  54702b:	e8 60 89 f8 ff       	call   0x4cf990
  547030:	ba 16 c6 58 00       	mov    edx,0x58c616
  547035:	33 c9                	xor    ecx,ecx
  547037:	e8 54 89 f8 ff       	call   0x4cf990
  54703c:	ba c8 50 59 00       	mov    edx,0x5950c8
  547041:	b9 1b 00 00 00       	mov    ecx,0x1b
  547046:	e8 45 89 f8 ff       	call   0x4cf990
  54704b:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  547050:	e8 5b 8f f8 ff       	call   0x4cffb0
  547055:	e8 c6 a0 f8 ff       	call   0x4d1120
  54705a:	83 f8 64             	cmp    eax,0x64
  54705d:	7d f1                	jge    0x547050
  54705f:	85 c0                	test   eax,eax
  547061:	78 ed                	js     0x547050
  547063:	69 c0 e8 00 00 00    	imul   eax,eax,0xe8
  547069:	8b 80 d8 ef 34 06    	mov    eax,DWORD PTR [eax+0x634efd8]
  54706f:	85 c0                	test   eax,eax
  547071:	74 dd                	je     0x547050
  547073:	83 f8 1b             	cmp    eax,0x1b
  547076:	75 0b                	jne    0x547083
  547078:	bf 01 00 00 00       	mov    edi,0x1
  54707d:	89 3d 88 fd 61 0a    	mov    DWORD PTR ds:0xa61fd88,edi
  547083:	83 c0 bf             	add    eax,0xffffffbf
  547086:	83 f8 13             	cmp    eax,0x13
  547089:	77 67                	ja     0x5470f2
  54708b:	0f b6 80 a0 71 54 00 	movzx  eax,BYTE PTR [eax+0x5471a0]
  547092:	ff 24 85 80 71 54 00 	jmp    DWORD PTR [eax*4+0x547180]
  547099:	c7 05 b8 3a 61 0a 00 	mov    DWORD PTR ds:0xa613ab8,0x0
  5470a0:	00 00 00 
  5470a3:	eb 46                	jmp    0x5470eb
  5470a5:	c7 05 b8 3a 61 0a 04 	mov    DWORD PTR ds:0xa613ab8,0x4
  5470ac:	00 00 00 
  5470af:	eb 3a                	jmp    0x5470eb
  5470b1:	c7 05 b8 3a 61 0a 07 	mov    DWORD PTR ds:0xa613ab8,0x7
  5470b8:	00 00 00 
  5470bb:	eb 2e                	jmp    0x5470eb
  5470bd:	c7 05 b8 3a 61 0a 06 	mov    DWORD PTR ds:0xa613ab8,0x6
  5470c4:	00 00 00 
  5470c7:	eb 22                	jmp    0x5470eb
  5470c9:	c7 05 b8 3a 61 0a 02 	mov    DWORD PTR ds:0xa613ab8,0x2
  5470d0:	00 00 00 
  5470d3:	eb 16                	jmp    0x5470eb
  5470d5:	c7 05 b8 3a 61 0a 05 	mov    DWORD PTR ds:0xa613ab8,0x5
  5470dc:	00 00 00 
  5470df:	eb 0a                	jmp    0x5470eb
  5470e1:	c7 05 b8 3a 61 0a 03 	mov    DWORD PTR ds:0xa613ab8,0x3
  5470e8:	00 00 00 
  5470eb:	e8 80 ae ff ff       	call   0x541f70
  5470f0:	8b f8                	mov    edi,eax
