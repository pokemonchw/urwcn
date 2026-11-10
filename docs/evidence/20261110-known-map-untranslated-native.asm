; VA 004E3020..004E3A43; image base 00400000
  4e3020:	55                   	push   ebp
  4e3021:	8b ec                	mov    ebp,esp
  4e3023:	83 ec 2c             	sub    esp,0x2c
  4e3026:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4e302b:	33 c5                	xor    eax,ebp
  4e302d:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4e3030:	53                   	push   ebx
  4e3031:	56                   	push   esi
  4e3032:	8b 35 60 ef 58 00    	mov    esi,DWORD PTR ds:0x58ef60
  4e3038:	57                   	push   edi
  4e3039:	6a 00                	push   0x0
  4e303b:	6a 00                	push   0x0
  4e303d:	6a 00                	push   0x0
  4e303f:	6a 00                	push   0x0
  4e3041:	6a 20                	push   0x20
  4e3043:	68 be 00 00 00       	push   0xbe
  4e3048:	68 c8 00 00 00       	push   0xc8
  4e304d:	6a 00                	push   0x0
  4e304f:	ff 15 f0 c1 58 00    	call   DWORD PTR ds:0x58c1f0
  4e3055:	50                   	push   eax
  4e3056:	89 45 d8             	mov    DWORD PTR [ebp-0x28],eax
  4e3059:	ff 15 20 c2 58 00    	call   DWORD PTR ds:0x58c220
  4e305f:	83 c4 24             	add    esp,0x24
  4e3062:	8b d8                	mov    ebx,eax
  4e3064:	33 d2                	xor    edx,edx
  4e3066:	89 5d e0             	mov    DWORD PTR [ebp-0x20],ebx
  4e3069:	8b cb                	mov    ecx,ebx
  4e306b:	ff 35 ac 87 5e 00    	push   DWORD PTR ds:0x5e87ac
  4e3071:	6a 28                	push   0x28
  4e3073:	68 b8 69 5a 00       	push   0x5a69b8
  4e3078:	68 be 00 00 00       	push   0xbe
  4e307d:	68 c8 00 00 00       	push   0xc8
  4e3082:	6a 00                	push   0x0
  4e3084:	e8 37 36 03 00       	call   0x5166c0
  4e3089:	8b 15 b4 cb 35 06    	mov    edx,DWORD PTR ds:0x635cbb4
  4e308f:	83 c4 18             	add    esp,0x18
  4e3092:	a1 a8 87 5e 00       	mov    eax,ds:0x5e87a8
  4e3097:	89 45 e4             	mov    DWORD PTR [ebp-0x1c],eax
  4e309a:	85 d2                	test   edx,edx
  4e309c:	75 0a                	jne    0x4e30a8
  4e309e:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4e30a5:	00 
  4e30a6:	eb 18                	jmp    0x4e30c0
  4e30a8:	b9 00 02 00 00       	mov    ecx,0x200
  4e30ad:	2b ca                	sub    ecx,edx
  4e30af:	03 c9                	add    ecx,ecx
  4e30b1:	66 0f 6e c1          	movd   xmm0,ecx
  4e30b5:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4e30b8:	f3 0f 59 05 80 d0 5d 	mulss  xmm0,DWORD PTR ds:0x5dd080
  4e30bf:	00 
  4e30c0:	f3 0f 59 05 38 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd538
  4e30c7:	00 
  4e30c8:	b9 04 00 00 00       	mov    ecx,0x4
  4e30cd:	ba 19 00 00 00       	mov    edx,0x19
  4e30d2:	c7 45 ec 19 00 00 00 	mov    DWORD PTR [ebp-0x14],0x19
  4e30d9:	ff 75 e7             	push   DWORD PTR [ebp-0x19]
  4e30dc:	c7 45 f0 21 00 00 00 	mov    DWORD PTR [ebp-0x10],0x21
  4e30e3:	ff 75 e6             	push   DWORD PTR [ebp-0x1a]
  4e30e6:	f3 0f 2c f8          	cvttss2si edi,xmm0
  4e30ea:	ff 75 e5             	push   DWORD PTR [ebp-0x1b]
  4e30ed:	3b f9                	cmp    edi,ecx
  4e30ef:	50                   	push   eax
  4e30f0:	0f 4c f9             	cmovl  edi,ecx
  4e30f3:	57                   	push   edi
  4e30f4:	6a 21                	push   0x21
  4e30f6:	8d 0c 3f             	lea    ecx,[edi+edi*1]
  4e30f9:	89 4d f4             	mov    DWORD PTR [ebp-0xc],ecx
  4e30fc:	89 4d f8             	mov    DWORD PTR [ebp-0x8],ecx
  4e30ff:	8b cb                	mov    ecx,ebx
  4e3101:	e8 1a 5f 02 00       	call   0x509020
  4e3106:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e3109:	83 c4 14             	add    esp,0x14
  4e310c:	8b cb                	mov    ecx,ebx
  4e310e:	6a 00                	push   0x0
  4e3110:	6a 00                	push   0x0
  4e3112:	6a 00                	push   0x0
  4e3114:	57                   	push   edi
  4e3115:	57                   	push   edi
  4e3116:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e3119:	e8 42 61 02 00       	call   0x509260
  4e311e:	83 c4 1c             	add    esp,0x1c
  4e3121:	ba 28 00 00 00       	mov    edx,0x28
  4e3126:	8b cb                	mov    ecx,ebx
  4e3128:	6a 00                	push   0x0
  4e312a:	56                   	push   esi
  4e312b:	68 d0 69 5a 00       	push   0x5a69d0
  4e3130:	6a 1e                	push   0x1e
  4e3132:	e8 29 b1 02 00       	call   0x50e260
  4e3137:	8b 15 b4 cb 35 06    	mov    edx,DWORD PTR ds:0x635cbb4
  4e313d:	83 c4 10             	add    esp,0x10
  4e3140:	8b 0d 98 87 5e 00    	mov    ecx,DWORD PTR ds:0x5e8798
  4e3146:	89 4d e4             	mov    DWORD PTR [ebp-0x1c],ecx
  4e3149:	85 d2                	test   edx,edx
  4e314b:	75 0a                	jne    0x4e3157
  4e314d:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4e3154:	00 
  4e3155:	eb 18                	jmp    0x4e316f
  4e3157:	b8 00 02 00 00       	mov    eax,0x200
  4e315c:	2b c2                	sub    eax,edx
  4e315e:	03 c0                	add    eax,eax
  4e3160:	66 0f 6e c0          	movd   xmm0,eax
  4e3164:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4e3167:	f3 0f 59 05 80 d0 5d 	mulss  xmm0,DWORD PTR ds:0x5dd080
  4e316e:	00 
  4e316f:	f3 0f 59 05 38 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd538
  4e3176:	00 
  4e3177:	ba 04 00 00 00       	mov    edx,0x4
  4e317c:	ff 75 e7             	push   DWORD PTR [ebp-0x19]
  4e317f:	ff 75 e6             	push   DWORD PTR [ebp-0x1a]
  4e3182:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4e3186:	ff 75 e5             	push   DWORD PTR [ebp-0x1b]
  4e3189:	83 f8 04             	cmp    eax,0x4
  4e318c:	51                   	push   ecx
  4e318d:	0f 4c c2             	cmovl  eax,edx
  4e3190:	53                   	push   ebx
  4e3191:	8d 3c 00             	lea    edi,[eax+eax*1]
  4e3194:	8b c7                	mov    eax,edi
  4e3196:	89 7d f4             	mov    DWORD PTR [ebp-0xc],edi
  4e3199:	99                   	cdq
  4e319a:	2b c2                	sub    eax,edx
  4e319c:	89 7d f8             	mov    DWORD PTR [ebp-0x8],edi
  4e319f:	d1 f8                	sar    eax,1
  4e31a1:	ba 19 00 00 00       	mov    edx,0x19
  4e31a6:	2b d0                	sub    edx,eax
  4e31a8:	8b c7                	mov    eax,edi
  4e31aa:	89 55 ec             	mov    DWORD PTR [ebp-0x14],edx
  4e31ad:	99                   	cdq
  4e31ae:	2b c2                	sub    eax,edx
  4e31b0:	ba 35 00 00 00       	mov    edx,0x35
  4e31b5:	d1 f8                	sar    eax,1
  4e31b7:	2b d0                	sub    edx,eax
  4e31b9:	89 55 f0             	mov    DWORD PTR [ebp-0x10],edx
  4e31bc:	ff 15 e4 c1 58 00    	call   DWORD PTR ds:0x58c1e4
  4e31c2:	83 c4 14             	add    esp,0x14
  4e31c5:	6a 00                	push   0x0
  4e31c7:	53                   	push   ebx
  4e31c8:	ff 15 fc c1 58 00    	call   DWORD PTR ds:0x58c1fc
  4e31ce:	8d 45 ec             	lea    eax,[ebp-0x14]
  4e31d1:	50                   	push   eax
  4e31d2:	53                   	push   ebx
  4e31d3:	ff 15 ec c1 58 00    	call   DWORD PTR ds:0x58c1ec
  4e31d9:	8b 4d f0             	mov    ecx,DWORD PTR [ebp-0x10]
  4e31dc:	8b 45 f8             	mov    eax,DWORD PTR [ebp-0x8]
  4e31df:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e31e2:	03 c1                	add    eax,ecx
  4e31e4:	50                   	push   eax
  4e31e5:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]
  4e31e8:	03 c2                	add    eax,edx
  4e31ea:	50                   	push   eax
  4e31eb:	51                   	push   ecx
  4e31ec:	8b cb                	mov    ecx,ebx
  4e31ee:	e8 cd 5a 02 00       	call   0x508cc0
  4e31f3:	83 c4 1c             	add    esp,0x1c
  4e31f6:	ba 28 00 00 00       	mov    edx,0x28
  4e31fb:	8b cb                	mov    ecx,ebx
  4e31fd:	6a 00                	push   0x0
  4e31ff:	56                   	push   esi
  4e3200:	68 20 dc 58 00       	push   0x58dc20
  4e3205:	6a 32                	push   0x32
  4e3207:	e8 54 b0 02 00       	call   0x50e260
  4e320c:	8b 15 b4 cb 35 06    	mov    edx,DWORD PTR ds:0x635cbb4
  4e3212:	83 c4 10             	add    esp,0x10
  4e3215:	a1 ac 87 5e 00       	mov    eax,ds:0x5e87ac
  4e321a:	89 45 e4             	mov    DWORD PTR [ebp-0x1c],eax
  4e321d:	85 d2                	test   edx,edx
  4e321f:	75 0a                	jne    0x4e322b
  4e3221:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4e3228:	00 
  4e3229:	eb 18                	jmp    0x4e3243
  4e322b:	b9 00 02 00 00       	mov    ecx,0x200
  4e3230:	2b ca                	sub    ecx,edx
  4e3232:	03 c9                	add    ecx,ecx
  4e3234:	66 0f 6e c1          	movd   xmm0,ecx
  4e3238:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4e323b:	f3 0f 59 05 80 d0 5d 	mulss  xmm0,DWORD PTR ds:0x5dd080
  4e3242:	00 
  4e3243:	f3 0f 59 05 38 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd538
  4e324a:	00 
  4e324b:	b9 04 00 00 00       	mov    ecx,0x4
  4e3250:	ba 19 00 00 00       	mov    edx,0x19
  4e3255:	c7 45 ec 19 00 00 00 	mov    DWORD PTR [ebp-0x14],0x19
  4e325c:	c7 45 f0 41 00 00 00 	mov    DWORD PTR [ebp-0x10],0x41
  4e3263:	f3 0f 2c d8          	cvttss2si ebx,xmm0
  4e3267:	83 fb 04             	cmp    ebx,0x4
  4e326a:	0f 4c d9             	cmovl  ebx,ecx
  4e326d:	2b d3                	sub    edx,ebx
  4e326f:	8d 0c 1b             	lea    ecx,[ebx+ebx*1]
  4e3272:	89 4d f4             	mov    DWORD PTR [ebp-0xc],ecx
  4e3275:	89 4d f8             	mov    DWORD PTR [ebp-0x8],ecx
  4e3278:	8d 4b 41             	lea    ecx,[ebx+0x41]
  4e327b:	51                   	push   ecx
  4e327c:	ff 75 e6             	push   DWORD PTR [ebp-0x1a]
  4e327f:	ff 75 e5             	push   DWORD PTR [ebp-0x1b]
  4e3282:	50                   	push   eax
  4e3283:	51                   	push   ecx
  4e3284:	8d 43 19             	lea    eax,[ebx+0x19]
  4e3287:	50                   	push   eax
  4e3288:	b8 41 00 00 00       	mov    eax,0x41
  4e328d:	2b c3                	sub    eax,ebx
  4e328f:	50                   	push   eax
  4e3290:	6a 19                	push   0x19
  4e3292:	51                   	push   ecx
  4e3293:	8b 4d e0             	mov    ecx,DWORD PTR [ebp-0x20]
  4e3296:	e8 a5 6b 02 00       	call   0x509e40
  4e329b:	8b 4d f0             	mov    ecx,DWORD PTR [ebp-0x10]
  4e329e:	83 c4 14             	add    esp,0x14
  4e32a1:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e32a4:	8d 3c 0b             	lea    edi,[ebx+ecx*1]
  4e32a7:	2b cb                	sub    ecx,ebx
  4e32a9:	57                   	push   edi
  4e32aa:	8d 04 13             	lea    eax,[ebx+edx*1]
  4e32ad:	50                   	push   eax
  4e32ae:	51                   	push   ecx
  4e32af:	52                   	push   edx
  4e32b0:	57                   	push   edi
  4e32b1:	8b 7d e0             	mov    edi,DWORD PTR [ebp-0x20]
  4e32b4:	2b d3                	sub    edx,ebx
  4e32b6:	8b cf                	mov    ecx,edi
  4e32b8:	e8 f3 6a 02 00       	call   0x509db0
  4e32bd:	83 c4 24             	add    esp,0x24
  4e32c0:	ba 28 00 00 00       	mov    edx,0x28
  4e32c5:	8b cf                	mov    ecx,edi
  4e32c7:	6a 00                	push   0x0
  4e32c9:	56                   	push   esi
  4e32ca:	68 60 d6 58 00       	push   0x58d660
  4e32cf:	6a 3e                	push   0x3e
  4e32d1:	e8 8a af 02 00       	call   0x50e260
  4e32d6:	8b 15 b4 cb 35 06    	mov    edx,DWORD PTR ds:0x635cbb4
  4e32dc:	83 c4 10             	add    esp,0x10
  4e32df:	a1 38 ef 58 00       	mov    eax,ds:0x58ef38
  4e32e4:	89 45 e4             	mov    DWORD PTR [ebp-0x1c],eax
  4e32e7:	85 d2                	test   edx,edx
  4e32e9:	75 0a                	jne    0x4e32f5
  4e32eb:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4e32f2:	00 
  4e32f3:	eb 18                	jmp    0x4e330d
  4e32f5:	b9 00 02 00 00       	mov    ecx,0x200
  4e32fa:	2b ca                	sub    ecx,edx
  4e32fc:	03 c9                	add    ecx,ecx
  4e32fe:	66 0f 6e c1          	movd   xmm0,ecx
  4e3302:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4e3305:	f3 0f 59 05 80 d0 5d 	mulss  xmm0,DWORD PTR ds:0x5dd080
  4e330c:	00 
  4e330d:	f3 0f 59 05 38 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd538
  4e3314:	00 
  4e3315:	b9 04 00 00 00       	mov    ecx,0x4
  4e331a:	ba 19 00 00 00       	mov    edx,0x19
  4e331f:	c7 45 ec 19 00 00 00 	mov    DWORD PTR [ebp-0x14],0x19
  4e3326:	c7 45 f0 4d 00 00 00 	mov    DWORD PTR [ebp-0x10],0x4d
  4e332d:	f3 0f 2c d8          	cvttss2si ebx,xmm0
  4e3331:	83 fb 04             	cmp    ebx,0x4
  4e3334:	0f 4c d9             	cmovl  ebx,ecx
  4e3337:	2b d3                	sub    edx,ebx
  4e3339:	8d 0c 1b             	lea    ecx,[ebx+ebx*1]
  4e333c:	89 4d f4             	mov    DWORD PTR [ebp-0xc],ecx
  4e333f:	89 4d f8             	mov    DWORD PTR [ebp-0x8],ecx
  4e3342:	8d 4b 4d             	lea    ecx,[ebx+0x4d]
  4e3345:	51                   	push   ecx
  4e3346:	ff 75 e6             	push   DWORD PTR [ebp-0x1a]
  4e3349:	ff 75 e5             	push   DWORD PTR [ebp-0x1b]
  4e334c:	50                   	push   eax
  4e334d:	51                   	push   ecx
  4e334e:	8d 43 19             	lea    eax,[ebx+0x19]
  4e3351:	50                   	push   eax
  4e3352:	b8 4d 00 00 00       	mov    eax,0x4d
  4e3357:	2b c3                	sub    eax,ebx
  4e3359:	50                   	push   eax
  4e335a:	6a 19                	push   0x19
  4e335c:	51                   	push   ecx
  4e335d:	8b cf                	mov    ecx,edi
  4e335f:	e8 dc 6a 02 00       	call   0x509e40
  4e3364:	8b 4d f0             	mov    ecx,DWORD PTR [ebp-0x10]
  4e3367:	83 c4 14             	add    esp,0x14
  4e336a:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e336d:	8d 3c 0b             	lea    edi,[ebx+ecx*1]
  4e3370:	2b cb                	sub    ecx,ebx
  4e3372:	57                   	push   edi
  4e3373:	8d 04 13             	lea    eax,[ebx+edx*1]
  4e3376:	50                   	push   eax
  4e3377:	51                   	push   ecx
  4e3378:	52                   	push   edx
  4e3379:	2b d3                	sub    edx,ebx
  4e337b:	8b 5d e0             	mov    ebx,DWORD PTR [ebp-0x20]
  4e337e:	57                   	push   edi
  4e337f:	8b cb                	mov    ecx,ebx
  4e3381:	e8 2a 6a 02 00       	call   0x509db0
  4e3386:	83 c4 24             	add    esp,0x24
  4e3389:	ba 28 00 00 00       	mov    edx,0x28
  4e338e:	8b cb                	mov    ecx,ebx
  4e3390:	6a 00                	push   0x0
  4e3392:	56                   	push   esi
  4e3393:	68 0c d7 58 00       	push   0x58d70c
  4e3398:	6a 4a                	push   0x4a
  4e339a:	e8 c1 ae 02 00       	call   0x50e260
  4e339f:	8b 15 b4 cb 35 06    	mov    edx,DWORD PTR ds:0x635cbb4
  4e33a5:	83 c4 10             	add    esp,0x10
  4e33a8:	8b 0d 38 ef 58 00    	mov    ecx,DWORD PTR ds:0x58ef38
  4e33ae:	89 4d e4             	mov    DWORD PTR [ebp-0x1c],ecx
  4e33b1:	85 d2                	test   edx,edx
  4e33b3:	75 0a                	jne    0x4e33bf
  4e33b5:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4e33bc:	00 
  4e33bd:	eb 18                	jmp    0x4e33d7
  4e33bf:	b8 00 02 00 00       	mov    eax,0x200
  4e33c4:	2b c2                	sub    eax,edx
  4e33c6:	03 c0                	add    eax,eax
  4e33c8:	66 0f 6e c0          	movd   xmm0,eax
  4e33cc:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4e33cf:	f3 0f 59 05 80 d0 5d 	mulss  xmm0,DWORD PTR ds:0x5dd080
  4e33d6:	00 
  4e33d7:	f3 0f 59 05 38 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd538
  4e33de:	00 
  4e33df:	ba 04 00 00 00       	mov    edx,0x4
  4e33e4:	ff 75 e7             	push   DWORD PTR [ebp-0x19]
  4e33e7:	ff 75 e6             	push   DWORD PTR [ebp-0x1a]
  4e33ea:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4e33ee:	ff 75 e5             	push   DWORD PTR [ebp-0x1b]
  4e33f1:	83 f8 04             	cmp    eax,0x4
  4e33f4:	51                   	push   ecx
  4e33f5:	0f 4c c2             	cmovl  eax,edx
  4e33f8:	53                   	push   ebx
  4e33f9:	8d 3c 00             	lea    edi,[eax+eax*1]
  4e33fc:	8b c7                	mov    eax,edi
  4e33fe:	89 7d f4             	mov    DWORD PTR [ebp-0xc],edi
  4e3401:	99                   	cdq
  4e3402:	2b c2                	sub    eax,edx
  4e3404:	89 7d f8             	mov    DWORD PTR [ebp-0x8],edi
  4e3407:	d1 f8                	sar    eax,1
  4e3409:	ba 19 00 00 00       	mov    edx,0x19
  4e340e:	2b d0                	sub    edx,eax
  4e3410:	8b c7                	mov    eax,edi
  4e3412:	89 55 ec             	mov    DWORD PTR [ebp-0x14],edx
  4e3415:	99                   	cdq
  4e3416:	2b c2                	sub    eax,edx
  4e3418:	ba 59 00 00 00       	mov    edx,0x59
  4e341d:	d1 f8                	sar    eax,1
  4e341f:	2b d0                	sub    edx,eax
  4e3421:	89 55 f0             	mov    DWORD PTR [ebp-0x10],edx
  4e3424:	ff 15 e4 c1 58 00    	call   DWORD PTR ds:0x58c1e4
  4e342a:	83 c4 14             	add    esp,0x14
  4e342d:	6a 00                	push   0x0
  4e342f:	53                   	push   ebx
  4e3430:	ff 15 fc c1 58 00    	call   DWORD PTR ds:0x58c1fc
  4e3436:	8d 45 ec             	lea    eax,[ebp-0x14]
  4e3439:	50                   	push   eax
  4e343a:	53                   	push   ebx
  4e343b:	ff 15 ec c1 58 00    	call   DWORD PTR ds:0x58c1ec
  4e3441:	8b 4d f0             	mov    ecx,DWORD PTR [ebp-0x10]
  4e3444:	8b 45 f8             	mov    eax,DWORD PTR [ebp-0x8]
  4e3447:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e344a:	03 c1                	add    eax,ecx
  4e344c:	50                   	push   eax
  4e344d:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]
  4e3450:	03 c2                	add    eax,edx
  4e3452:	50                   	push   eax
  4e3453:	51                   	push   ecx
  4e3454:	8b cb                	mov    ecx,ebx
  4e3456:	e8 65 58 02 00       	call   0x508cc0
  4e345b:	83 c4 1c             	add    esp,0x1c
  4e345e:	ba 28 00 00 00       	mov    edx,0x28
  4e3463:	8b cb                	mov    ecx,ebx
  4e3465:	6a 00                	push   0x0
  4e3467:	56                   	push   esi
  4e3468:	68 00 d5 58 00       	push   0x58d500
  4e346d:	6a 56                	push   0x56
  4e346f:	e8 ec ad 02 00       	call   0x50e260
  4e3474:	8b 15 b4 cb 35 06    	mov    edx,DWORD PTR ds:0x635cbb4
  4e347a:	83 c4 10             	add    esp,0x10
  4e347d:	a1 6c ef 58 00       	mov    eax,ds:0x58ef6c
  4e3482:	89 45 e4             	mov    DWORD PTR [ebp-0x1c],eax
  4e3485:	85 d2                	test   edx,edx
  4e3487:	75 0a                	jne    0x4e3493
  4e3489:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4e3490:	00 
  4e3491:	eb 18                	jmp    0x4e34ab
  4e3493:	b9 00 02 00 00       	mov    ecx,0x200
  4e3498:	2b ca                	sub    ecx,edx
  4e349a:	03 c9                	add    ecx,ecx
  4e349c:	66 0f 6e c1          	movd   xmm0,ecx
  4e34a0:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4e34a3:	f3 0f 59 05 80 d0 5d 	mulss  xmm0,DWORD PTR ds:0x5dd080
  4e34aa:	00 
  4e34ab:	f3 0f 59 05 38 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd538
  4e34b2:	00 
  4e34b3:	b9 04 00 00 00       	mov    ecx,0x4
  4e34b8:	ba 19 00 00 00       	mov    edx,0x19
  4e34bd:	c7 45 ec 19 00 00 00 	mov    DWORD PTR [ebp-0x14],0x19
  4e34c4:	ff 75 e7             	push   DWORD PTR [ebp-0x19]
  4e34c7:	c7 45 f0 65 00 00 00 	mov    DWORD PTR [ebp-0x10],0x65
  4e34ce:	ff 75 e6             	push   DWORD PTR [ebp-0x1a]
  4e34d1:	f3 0f 2c f8          	cvttss2si edi,xmm0
  4e34d5:	ff 75 e5             	push   DWORD PTR [ebp-0x1b]
  4e34d8:	83 ff 04             	cmp    edi,0x4
  4e34db:	50                   	push   eax
  4e34dc:	0f 4c f9             	cmovl  edi,ecx
  4e34df:	57                   	push   edi
  4e34e0:	6a 65                	push   0x65
  4e34e2:	8d 0c 3f             	lea    ecx,[edi+edi*1]
  4e34e5:	89 4d f4             	mov    DWORD PTR [ebp-0xc],ecx
  4e34e8:	89 4d f8             	mov    DWORD PTR [ebp-0x8],ecx
  4e34eb:	8b cb                	mov    ecx,ebx
  4e34ed:	e8 2e 5b 02 00       	call   0x509020
  4e34f2:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e34f5:	83 c4 14             	add    esp,0x14
  4e34f8:	8b cb                	mov    ecx,ebx
  4e34fa:	6a 00                	push   0x0
  4e34fc:	6a 00                	push   0x0
  4e34fe:	6a 00                	push   0x0
  4e3500:	57                   	push   edi
  4e3501:	57                   	push   edi
  4e3502:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e3505:	e8 56 5d 02 00       	call   0x509260
  4e350a:	83 c4 1c             	add    esp,0x1c
  4e350d:	ba 28 00 00 00       	mov    edx,0x28
  4e3512:	8b cb                	mov    ecx,ebx
  4e3514:	6a 00                	push   0x0
  4e3516:	56                   	push   esi
  4e3517:	68 d4 69 5a 00       	push   0x5a69d4
  4e351c:	6a 62                	push   0x62
  4e351e:	e8 3d ad 02 00       	call   0x50e260
  4e3523:	8b 15 b4 cb 35 06    	mov    edx,DWORD PTR ds:0x635cbb4
  4e3529:	83 c4 10             	add    esp,0x10
  4e352c:	a1 ac 87 5e 00       	mov    eax,ds:0x5e87ac
  4e3531:	89 45 e4             	mov    DWORD PTR [ebp-0x1c],eax
  4e3534:	85 d2                	test   edx,edx
  4e3536:	75 0a                	jne    0x4e3542
  4e3538:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4e353f:	00 
  4e3540:	eb 18                	jmp    0x4e355a
  4e3542:	b9 00 02 00 00       	mov    ecx,0x200
  4e3547:	2b ca                	sub    ecx,edx
  4e3549:	03 c9                	add    ecx,ecx
  4e354b:	66 0f 6e c1          	movd   xmm0,ecx
  4e354f:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4e3552:	f3 0f 59 05 80 d0 5d 	mulss  xmm0,DWORD PTR ds:0x5dd080
  4e3559:	00 
  4e355a:	f3 0f 59 05 38 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd538
  4e3561:	00 
  4e3562:	b9 04 00 00 00       	mov    ecx,0x4
  4e3567:	ba 19 00 00 00       	mov    edx,0x19
  4e356c:	c7 45 ec 19 00 00 00 	mov    DWORD PTR [ebp-0x14],0x19
  4e3573:	ff 75 e7             	push   DWORD PTR [ebp-0x19]
  4e3576:	c7 45 f0 71 00 00 00 	mov    DWORD PTR [ebp-0x10],0x71
  4e357d:	ff 75 e6             	push   DWORD PTR [ebp-0x1a]
  4e3580:	f3 0f 2c f8          	cvttss2si edi,xmm0
  4e3584:	ff 75 e5             	push   DWORD PTR [ebp-0x1b]
  4e3587:	83 ff 04             	cmp    edi,0x4
  4e358a:	50                   	push   eax
  4e358b:	0f 4c f9             	cmovl  edi,ecx
  4e358e:	57                   	push   edi
  4e358f:	6a 71                	push   0x71
  4e3591:	8d 0c 3f             	lea    ecx,[edi+edi*1]
  4e3594:	89 4d f4             	mov    DWORD PTR [ebp-0xc],ecx
  4e3597:	89 4d f8             	mov    DWORD PTR [ebp-0x8],ecx
  4e359a:	8b cb                	mov    ecx,ebx
  4e359c:	e8 7f 5a 02 00       	call   0x509020
  4e35a1:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e35a4:	83 c4 14             	add    esp,0x14
  4e35a7:	8b cb                	mov    ecx,ebx
  4e35a9:	6a 00                	push   0x0
  4e35ab:	6a 00                	push   0x0
  4e35ad:	6a 00                	push   0x0
  4e35af:	57                   	push   edi
  4e35b0:	57                   	push   edi
  4e35b1:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e35b4:	e8 a7 5c 02 00       	call   0x509260
  4e35b9:	83 c4 1c             	add    esp,0x1c
  4e35bc:	ba 28 00 00 00       	mov    edx,0x28
  4e35c1:	8b cb                	mov    ecx,ebx
  4e35c3:	6a 00                	push   0x0
  4e35c5:	56                   	push   esi
  4e35c6:	68 1c 34 5a 00       	push   0x5a341c
  4e35cb:	6a 6e                	push   0x6e
  4e35cd:	e8 8e ac 02 00       	call   0x50e260
  4e35d2:	8b 0d b4 cb 35 06    	mov    ecx,DWORD PTR ds:0x635cbb4
  4e35d8:	83 c4 10             	add    esp,0x10
  4e35db:	8b 3d a8 87 5e 00    	mov    edi,DWORD PTR ds:0x5e87a8
  4e35e1:	89 7d e4             	mov    DWORD PTR [ebp-0x1c],edi
  4e35e4:	85 c9                	test   ecx,ecx
  4e35e6:	75 0a                	jne    0x4e35f2
  4e35e8:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4e35ef:	00 
  4e35f0:	eb 18                	jmp    0x4e360a
  4e35f2:	b8 00 02 00 00       	mov    eax,0x200
  4e35f7:	2b c1                	sub    eax,ecx
  4e35f9:	03 c0                	add    eax,eax
  4e35fb:	66 0f 6e c0          	movd   xmm0,eax
  4e35ff:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4e3602:	f3 0f 59 05 80 d0 5d 	mulss  xmm0,DWORD PTR ds:0x5dd080
  4e3609:	00 
  4e360a:	f3 0f 59 05 38 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd538
  4e3611:	00 
  4e3612:	b8 04 00 00 00       	mov    eax,0x4
  4e3617:	51                   	push   ecx
  4e3618:	8b 4d e0             	mov    ecx,DWORD PTR [ebp-0x20]
  4e361b:	ba 18 00 00 00       	mov    edx,0x18
  4e3620:	6a 00                	push   0x0
  4e3622:	f3 0f 2c d8          	cvttss2si ebx,xmm0
  4e3626:	6a 00                	push   0x0
  4e3628:	6a 00                	push   0x0
  4e362a:	6a 06                	push   0x6
  4e362c:	c7 45 ec 19 00 00 00 	mov    DWORD PTR [ebp-0x14],0x19
  4e3633:	c7 45 f0 80 00 00 00 	mov    DWORD PTR [ebp-0x10],0x80
  4e363a:	83 fb 04             	cmp    ebx,0x4
  4e363d:	0f 4c d8             	cmovl  ebx,eax
  4e3640:	2b d3                	sub    edx,ebx
  4e3642:	89 5d dc             	mov    DWORD PTR [ebp-0x24],ebx
  4e3645:	8d 04 1b             	lea    eax,[ebx+ebx*1]
  4e3648:	89 45 f4             	mov    DWORD PTR [ebp-0xc],eax
  4e364b:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  4e364e:	b8 7f 00 00 00       	mov    eax,0x7f
  4e3653:	2b c3                	sub    eax,ebx
  4e3655:	50                   	push   eax
  4e3656:	8d 43 1a             	lea    eax,[ebx+0x1a]
  4e3659:	50                   	push   eax
  4e365a:	8d 83 81 00 00 00    	lea    eax,[ebx+0x81]
  4e3660:	50                   	push   eax
  4e3661:	e8 fa 74 02 00       	call   0x50ab60
  4e3666:	8b 4d f0             	mov    ecx,DWORD PTR [ebp-0x10]
  4e3669:	83 c4 1c             	add    esp,0x1c
  4e366c:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e366f:	6a 00                	push   0x0
  4e3671:	6a 00                	push   0x0
  4e3673:	8d 41 01             	lea    eax,[ecx+0x1]
  4e3676:	2b cb                	sub    ecx,ebx
  4e3678:	6a 00                	push   0x0
  4e367a:	03 c3                	add    eax,ebx
  4e367c:	49                   	dec    ecx
  4e367d:	6a 06                	push   0x6
  4e367f:	50                   	push   eax
  4e3680:	8d 42 01             	lea    eax,[edx+0x1]
  4e3683:	2b d3                	sub    edx,ebx
  4e3685:	03 c3                	add    eax,ebx
  4e3687:	4a                   	dec    edx
  4e3688:	50                   	push   eax
  4e3689:	51                   	push   ecx
  4e368a:	8b 4d e0             	mov    ecx,DWORD PTR [ebp-0x20]
  4e368d:	e8 ce 74 02 00       	call   0x50ab60
  4e3692:	8b 5d e5             	mov    ebx,DWORD PTR [ebp-0x1b]
  4e3695:	83 c4 1c             	add    esp,0x1c
  4e3698:	8b 45 f0             	mov    eax,DWORD PTR [ebp-0x10]
  4e369b:	2b 45 dc             	sub    eax,DWORD PTR [ebp-0x24]
  4e369e:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e36a1:	ff 75 e6             	push   DWORD PTR [ebp-0x1a]
  4e36a4:	8b 4d e0             	mov    ecx,DWORD PTR [ebp-0x20]
  4e36a7:	53                   	push   ebx
  4e36a8:	57                   	push   edi
  4e36a9:	6a 02                	push   0x2
  4e36ab:	50                   	push   eax
  4e36ac:	8b 45 dc             	mov    eax,DWORD PTR [ebp-0x24]
  4e36af:	03 c2                	add    eax,edx
  4e36b1:	2b 55 dc             	sub    edx,DWORD PTR [ebp-0x24]
  4e36b4:	50                   	push   eax
  4e36b5:	8b 45 dc             	mov    eax,DWORD PTR [ebp-0x24]
  4e36b8:	03 45 f0             	add    eax,DWORD PTR [ebp-0x10]
  4e36bb:	50                   	push   eax
  4e36bc:	e8 9f 74 02 00       	call   0x50ab60
  4e36c1:	8b 4d f0             	mov    ecx,DWORD PTR [ebp-0x10]
  4e36c4:	83 c4 1c             	add    esp,0x1c
  4e36c7:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e36ca:	ff 75 e6             	push   DWORD PTR [ebp-0x1a]
  4e36cd:	53                   	push   ebx
  4e36ce:	8b 5d dc             	mov    ebx,DWORD PTR [ebp-0x24]
  4e36d1:	57                   	push   edi
  4e36d2:	6a 02                	push   0x2
  4e36d4:	8d 04 0b             	lea    eax,[ebx+ecx*1]
  4e36d7:	2b cb                	sub    ecx,ebx
  4e36d9:	50                   	push   eax
  4e36da:	8d 04 13             	lea    eax,[ebx+edx*1]
  4e36dd:	2b d3                	sub    edx,ebx
  4e36df:	50                   	push   eax
  4e36e0:	51                   	push   ecx
  4e36e1:	8b 5d e0             	mov    ebx,DWORD PTR [ebp-0x20]
  4e36e4:	8b cb                	mov    ecx,ebx
  4e36e6:	e8 75 74 02 00       	call   0x50ab60
  4e36eb:	6a 00                	push   0x0
  4e36ed:	56                   	push   esi
  4e36ee:	68 dc 69 5a 00       	push   0x5a69dc
  4e36f3:	6a 7d                	push   0x7d
  4e36f5:	ba 28 00 00 00       	mov    edx,0x28
  4e36fa:	8b cb                	mov    ecx,ebx
  4e36fc:	e8 5f ab 02 00       	call   0x50e260
  4e3701:	8b 0d b4 cb 35 06    	mov    ecx,DWORD PTR ds:0x635cbb4
  4e3707:	83 c4 30             	add    esp,0x30
  4e370a:	85 c9                	test   ecx,ecx
  4e370c:	75 0a                	jne    0x4e3718
  4e370e:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4e3715:	00 
  4e3716:	eb 18                	jmp    0x4e3730
  4e3718:	b8 00 02 00 00       	mov    eax,0x200
  4e371d:	2b c1                	sub    eax,ecx
  4e371f:	03 c0                	add    eax,eax
  4e3721:	66 0f 6e c0          	movd   xmm0,eax
  4e3725:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4e3728:	f3 0f 59 05 80 d0 5d 	mulss  xmm0,DWORD PTR ds:0x5dd080
  4e372f:	00 
  4e3730:	f3 0f 59 05 44 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd544
  4e3737:	00 
  4e3738:	b8 04 00 00 00       	mov    eax,0x4
  4e373d:	51                   	push   ecx
  4e373e:	68 b4 00 00 00       	push   0xb4
  4e3743:	68 82 00 00 00       	push   0x82
  4e3748:	f3 0f 2c f8          	cvttss2si edi,xmm0
  4e374c:	6a 46                	push   0x46
  4e374e:	ba 19 00 00 00       	mov    edx,0x19
  4e3753:	c7 45 ec 19 00 00 00 	mov    DWORD PTR [ebp-0x14],0x19
  4e375a:	8b cb                	mov    ecx,ebx
  4e375c:	c7 45 f0 8f 00 00 00 	mov    DWORD PTR [ebp-0x10],0x8f
  4e3763:	83 ff 04             	cmp    edi,0x4
  4e3766:	0f 4c f8             	cmovl  edi,eax
  4e3769:	8d 04 3f             	lea    eax,[edi+edi*1]
  4e376c:	89 45 f4             	mov    DWORD PTR [ebp-0xc],eax
  4e376f:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  4e3772:	8d 47 ff             	lea    eax,[edi-0x1]
  4e3775:	0f b7 c0             	movzx  eax,ax
  4e3778:	50                   	push   eax
  4e3779:	50                   	push   eax
  4e377a:	68 8f 00 00 00       	push   0x8f
  4e377f:	e8 dc 5a 02 00       	call   0x509260
  4e3784:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e3787:	83 c4 18             	add    esp,0x18
  4e378a:	8b cb                	mov    ecx,ebx
  4e378c:	68 b4 00 00 00       	push   0xb4
  4e3791:	68 82 00 00 00       	push   0x82
  4e3796:	6a 46                	push   0x46
  4e3798:	57                   	push   edi
  4e3799:	57                   	push   edi
  4e379a:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e379d:	e8 be 5a 02 00       	call   0x509260
  4e37a2:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e37a5:	8d 47 01             	lea    eax,[edi+0x1]
  4e37a8:	83 c4 18             	add    esp,0x18
  4e37ab:	0f b7 c0             	movzx  eax,ax
  4e37ae:	8b cb                	mov    ecx,ebx
  4e37b0:	68 b4 00 00 00       	push   0xb4
  4e37b5:	68 82 00 00 00       	push   0x82
  4e37ba:	6a 46                	push   0x46
  4e37bc:	50                   	push   eax
  4e37bd:	50                   	push   eax
  4e37be:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e37c1:	e8 9a 5a 02 00       	call   0x509260
  4e37c6:	8b 4d f0             	mov    ecx,DWORD PTR [ebp-0x10]
  4e37c9:	83 c4 18             	add    esp,0x18
  4e37cc:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e37cf:	6a 00                	push   0x0
  4e37d1:	6a 00                	push   0x0
  4e37d3:	6a 00                	push   0x0
  4e37d5:	8d 04 0f             	lea    eax,[edi+ecx*1]
  4e37d8:	2b cf                	sub    ecx,edi
  4e37da:	6a 02                	push   0x2
  4e37dc:	50                   	push   eax
  4e37dd:	52                   	push   edx
  4e37de:	51                   	push   ecx
  4e37df:	8b cb                	mov    ecx,ebx
  4e37e1:	e8 7a 73 02 00       	call   0x50ab60
  4e37e6:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e37e9:	83 c4 1c             	add    esp,0x1c
  4e37ec:	8b 4d f0             	mov    ecx,DWORD PTR [ebp-0x10]
  4e37ef:	6a 00                	push   0x0
  4e37f1:	6a 00                	push   0x0
  4e37f3:	6a 00                	push   0x0
  4e37f5:	6a 02                	push   0x2
  4e37f7:	51                   	push   ecx
  4e37f8:	8d 04 17             	lea    eax,[edi+edx*1]
  4e37fb:	2b d7                	sub    edx,edi
  4e37fd:	50                   	push   eax
  4e37fe:	51                   	push   ecx
  4e37ff:	8b cb                	mov    ecx,ebx
  4e3801:	e8 5a 73 02 00       	call   0x50ab60
  4e3806:	83 c4 1c             	add    esp,0x1c
  4e3809:	8d 47 02             	lea    eax,[edi+0x2]
  4e380c:	0f b7 c0             	movzx  eax,ax
  4e380f:	6a 00                	push   0x0
  4e3811:	6a 00                	push   0x0
  4e3813:	6a 00                	push   0x0
  4e3815:	50                   	push   eax
  4e3816:	50                   	push   eax
  4e3817:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e381a:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e381d:	8b cb                	mov    ecx,ebx
  4e381f:	e8 3c 5a 02 00       	call   0x509260
  4e3824:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e3827:	8d 47 fe             	lea    eax,[edi-0x2]
  4e382a:	83 c4 18             	add    esp,0x18
  4e382d:	0f b7 c0             	movzx  eax,ax
  4e3830:	8b cb                	mov    ecx,ebx
  4e3832:	6a 00                	push   0x0
  4e3834:	6a 00                	push   0x0
  4e3836:	6a 00                	push   0x0
  4e3838:	50                   	push   eax
  4e3839:	50                   	push   eax
  4e383a:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e383d:	e8 1e 5a 02 00       	call   0x509260
  4e3842:	83 c4 1c             	add    esp,0x1c
  4e3845:	ba 28 00 00 00       	mov    edx,0x28
  4e384a:	8b cb                	mov    ecx,ebx
  4e384c:	6a 00                	push   0x0
  4e384e:	56                   	push   esi
  4e384f:	68 ec 69 5a 00       	push   0x5a69ec
  4e3854:	68 8c 00 00 00       	push   0x8c
  4e3859:	e8 02 aa 02 00       	call   0x50e260
  4e385e:	0f 28 05 70 d8 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd870
  4e3865:	ba 19 00 00 00       	mov    edx,0x19
  4e386a:	68 9b 00 00 00       	push   0x9b
  4e386f:	68 b4 00 00 00       	push   0xb4
  4e3874:	68 82 00 00 00       	push   0x82
  4e3879:	6a 46                	push   0x46
  4e387b:	6a 05                	push   0x5
  4e387d:	68 9e 00 00 00       	push   0x9e
  4e3882:	8b cb                	mov    ecx,ebx
  4e3884:	0f 11 45 ec          	movups XMMWORD PTR [ebp-0x14],xmm0
  4e3888:	e8 93 57 02 00       	call   0x509020
  4e388d:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e3890:	83 c4 24             	add    esp,0x24
  4e3893:	8b cb                	mov    ecx,ebx
  4e3895:	6a 00                	push   0x0
  4e3897:	6a 00                	push   0x0
  4e3899:	6a 00                	push   0x0
  4e389b:	6a 05                	push   0x5
  4e389d:	6a 05                	push   0x5
  4e389f:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e38a2:	e8 b9 59 02 00       	call   0x509260
  4e38a7:	83 c4 1c             	add    esp,0x1c
  4e38aa:	ba 28 00 00 00       	mov    edx,0x28
  4e38af:	8b cb                	mov    ecx,ebx
  4e38b1:	6a 00                	push   0x0
  4e38b3:	56                   	push   esi
  4e38b4:	68 fc 69 5a 00       	push   0x5a69fc
  4e38b9:	68 9b 00 00 00       	push   0x9b
  4e38be:	e8 9d a9 02 00       	call   0x50e260
  4e38c3:	8b 0d b4 cb 35 06    	mov    ecx,DWORD PTR ds:0x635cbb4
  4e38c9:	83 c4 10             	add    esp,0x10
  4e38cc:	85 c9                	test   ecx,ecx
  4e38ce:	75 0a                	jne    0x4e38da
  4e38d0:	f3 0f 10 05 c0 d1 5d 	movss  xmm0,DWORD PTR ds:0x5dd1c0
  4e38d7:	00 
  4e38d8:	eb 18                	jmp    0x4e38f2
  4e38da:	b8 00 02 00 00       	mov    eax,0x200
  4e38df:	2b c1                	sub    eax,ecx
  4e38e1:	03 c0                	add    eax,eax
  4e38e3:	66 0f 6e c0          	movd   xmm0,eax
  4e38e7:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4e38ea:	f3 0f 59 05 80 d0 5d 	mulss  xmm0,DWORD PTR ds:0x5dd080
  4e38f1:	00 
  4e38f2:	f3 0f 59 05 20 d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd520
  4e38f9:	00 
  4e38fa:	b8 04 00 00 00       	mov    eax,0x4
  4e38ff:	51                   	push   ecx
  4e3900:	6a 00                	push   0x0
  4e3902:	6a 00                	push   0x0
  4e3904:	f3 0f 2c f8          	cvttss2si edi,xmm0
  4e3908:	6a 00                	push   0x0
  4e390a:	ba 19 00 00 00       	mov    edx,0x19
  4e390f:	c7 45 ec 19 00 00 00 	mov    DWORD PTR [ebp-0x14],0x19
  4e3916:	8b cb                	mov    ecx,ebx
  4e3918:	c7 45 f0 ad 00 00 00 	mov    DWORD PTR [ebp-0x10],0xad
  4e391f:	83 ff 04             	cmp    edi,0x4
  4e3922:	0f 4c f8             	cmovl  edi,eax
  4e3925:	8d 04 3f             	lea    eax,[edi+edi*1]
  4e3928:	89 45 f4             	mov    DWORD PTR [ebp-0xc],eax
  4e392b:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  4e392e:	8d 47 fe             	lea    eax,[edi-0x2]
  4e3931:	0f b7 c0             	movzx  eax,ax
  4e3934:	50                   	push   eax
  4e3935:	50                   	push   eax
  4e3936:	68 ad 00 00 00       	push   0xad
  4e393b:	e8 20 59 02 00       	call   0x509260
  4e3940:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e3943:	8d 47 ff             	lea    eax,[edi-0x1]
  4e3946:	83 c4 18             	add    esp,0x18
  4e3949:	0f b7 c0             	movzx  eax,ax
  4e394c:	8b cb                	mov    ecx,ebx
  4e394e:	68 ff 00 00 00       	push   0xff
  4e3953:	68 ff 00 00 00       	push   0xff
  4e3958:	68 ff 00 00 00       	push   0xff
  4e395d:	50                   	push   eax
  4e395e:	50                   	push   eax
  4e395f:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e3962:	e8 f9 58 02 00       	call   0x509260
  4e3967:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e396a:	83 c4 18             	add    esp,0x18
  4e396d:	8b cb                	mov    ecx,ebx
  4e396f:	68 ff 00 00 00       	push   0xff
  4e3974:	68 ff 00 00 00       	push   0xff
  4e3979:	68 ff 00 00 00       	push   0xff
  4e397e:	57                   	push   edi
  4e397f:	57                   	push   edi
  4e3980:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e3983:	e8 d8 58 02 00       	call   0x509260
  4e3988:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e398b:	8d 47 01             	lea    eax,[edi+0x1]
  4e398e:	83 c4 18             	add    esp,0x18
  4e3991:	0f b7 c0             	movzx  eax,ax
  4e3994:	8b cb                	mov    ecx,ebx
  4e3996:	68 ff 00 00 00       	push   0xff
  4e399b:	68 ff 00 00 00       	push   0xff
  4e39a0:	68 ff 00 00 00       	push   0xff
  4e39a5:	50                   	push   eax
  4e39a6:	50                   	push   eax
  4e39a7:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e39aa:	e8 b1 58 02 00       	call   0x509260
  4e39af:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e39b2:	8d 47 02             	lea    eax,[edi+0x2]
  4e39b5:	83 c4 18             	add    esp,0x18
  4e39b8:	0f b7 c0             	movzx  eax,ax
  4e39bb:	8b cb                	mov    ecx,ebx
  4e39bd:	6a 00                	push   0x0
  4e39bf:	6a 00                	push   0x0
  4e39c1:	6a 00                	push   0x0
  4e39c3:	50                   	push   eax
  4e39c4:	50                   	push   eax
  4e39c5:	ff 75 f0             	push   DWORD PTR [ebp-0x10]
  4e39c8:	e8 93 58 02 00       	call   0x509260
  4e39cd:	83 c4 1c             	add    esp,0x1c
  4e39d0:	ba 28 00 00 00       	mov    edx,0x28
  4e39d5:	8b cb                	mov    ecx,ebx
  4e39d7:	6a 00                	push   0x0
  4e39d9:	56                   	push   esi
  4e39da:	68 10 6a 5a 00       	push   0x5a6a10
  4e39df:	68 aa 00 00 00       	push   0xaa
  4e39e4:	e8 77 a8 02 00       	call   0x50e260
  4e39e9:	a1 80 fa 38 06       	mov    eax,ds:0x638fa80
  4e39ee:	83 c4 10             	add    esp,0x10
  4e39f1:	85 c0                	test   eax,eax
  4e39f3:	74 14                	je     0x4e3a09
  4e39f5:	50                   	push   eax
  4e39f6:	ff 15 2c c2 58 00    	call   DWORD PTR ds:0x58c22c
  4e39fc:	83 c4 04             	add    esp,0x4
  4e39ff:	c7 05 80 fa 38 06 00 	mov    DWORD PTR ds:0x638fa80,0x0
  4e3a06:	00 00 00 
  4e3a09:	8b 75 d8             	mov    esi,DWORD PTR [ebp-0x28]
  4e3a0c:	56                   	push   esi
  4e3a0d:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3a13:	ff 15 e0 c1 58 00    	call   DWORD PTR ds:0x58c1e0
  4e3a19:	56                   	push   esi
  4e3a1a:	a3 80 fa 38 06       	mov    ds:0x638fa80,eax
  4e3a1f:	ff 15 f4 c1 58 00    	call   DWORD PTR ds:0x58c1f4
  4e3a25:	83 c4 0c             	add    esp,0xc
  4e3a28:	53                   	push   ebx
  4e3a29:	ff 15 18 c2 58 00    	call   DWORD PTR ds:0x58c218
  4e3a2f:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4e3a32:	83 c4 04             	add    esp,0x4
  4e3a35:	33 cd                	xor    ecx,ebp
  4e3a37:	5f                   	pop    edi
  4e3a38:	5e                   	pop    esi
  4e3a39:	5b                   	pop    ebx
  4e3a3a:	e8 6f 66 0a 00       	call   0x58a0ae
  4e3a3f:	8b e5                	mov    esp,ebp
  4e3a41:	5d                   	pop    ebp
  4e3a42:	c3                   	ret
; VA 004E3D90..004E4042; image base 00400000
  4e3d90:	55                   	push   ebp
  4e3d91:	8b ec                	mov    ebp,esp
  4e3d93:	83 ec 18             	sub    esp,0x18
  4e3d96:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4e3d9b:	33 c5                	xor    eax,ebp
  4e3d9d:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4e3da0:	a1 b0 37 39 06       	mov    eax,ds:0x63937b0
  4e3da5:	56                   	push   esi
  4e3da6:	57                   	push   edi
  4e3da7:	85 c0                	test   eax,eax
  4e3da9:	74 0a                	je     0x4e3db5
  4e3dab:	50                   	push   eax
  4e3dac:	ff 15 2c c2 58 00    	call   DWORD PTR ds:0x58c22c
  4e3db2:	83 c4 04             	add    esp,0x4
  4e3db5:	68 58 02 00 00       	push   0x258
  4e3dba:	68 20 03 00 00       	push   0x320
  4e3dbf:	6a 02                	push   0x2
  4e3dc1:	68 04 20 36 16       	push   0x16362004
  4e3dc6:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3dcc:	ff 15 08 c2 58 00    	call   DWORD PTR ds:0x58c208
  4e3dd2:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  4e3dd9:	83 c4 14             	add    esp,0x14
  4e3ddc:	8b 35 4c b6 5b 06    	mov    esi,DWORD PTR ds:0x65bb64c
  4e3de2:	8b 3d 88 c2 58 00    	mov    edi,DWORD PTR ds:0x58c288
  4e3de8:	a3 b0 37 39 06       	mov    ds:0x63937b0,eax
  4e3ded:	50                   	push   eax
  4e3dee:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3df4:	0f 11 45 ec          	movups XMMWORD PTR [ebp-0x14],xmm0
  4e3df8:	ff d7                	call   edi
  4e3dfa:	8d 45 ec             	lea    eax,[ebp-0x14]
  4e3dfd:	50                   	push   eax
  4e3dfe:	6a 00                	push   0x0
  4e3e00:	56                   	push   esi
  4e3e01:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3e07:	ff 15 28 c2 58 00    	call   DWORD PTR ds:0x58c228
  4e3e0d:	6a 00                	push   0x0
  4e3e0f:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3e15:	ff d7                	call   edi
  4e3e17:	8b 0d b0 37 39 06    	mov    ecx,DWORD PTR ds:0x63937b0
  4e3e1d:	ba 34 6a 5a 00       	mov    edx,0x5a6a34
  4e3e22:	e8 09 f6 02 00       	call   0x513430
  4e3e27:	b9 48 6a 5a 00       	mov    ecx,0x5a6a48
  4e3e2c:	e8 ff e6 07 00       	call   0x562530
  4e3e31:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  4e3e37:	ba 01 00 00 00       	mov    edx,0x1
  4e3e3c:	6a 00                	push   0x0
  4e3e3e:	ff 35 60 ef 58 00    	push   DWORD PTR ds:0x58ef60
  4e3e44:	6a ff                	push   0xffffffff
  4e3e46:	68 18 01 00 00       	push   0x118
  4e3e4b:	6a 01                	push   0x1
  4e3e4d:	e8 7e b1 02 00       	call   0x50efd0
  4e3e52:	83 c4 34             	add    esp,0x34
  4e3e55:	8b f0                	mov    esi,eax
  4e3e57:	ff 35 b0 37 39 06    	push   DWORD PTR ds:0x63937b0
  4e3e5d:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3e63:	ff d7                	call   edi
  4e3e65:	ff 35 60 ef 58 00    	push   DWORD PTR ds:0x58ef60
  4e3e6b:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  4e3e71:	8d 46 14             	lea    eax,[esi+0x14]
  4e3e74:	6a 24                	push   0x24
  4e3e76:	68 16 c6 58 00       	push   0x58c616
  4e3e7b:	50                   	push   eax
  4e3e7c:	68 2c 01 00 00       	push   0x12c
  4e3e81:	68 ea 01 00 00       	push   0x1ea
  4e3e86:	ba ea 01 00 00       	mov    edx,0x1ea
  4e3e8b:	e8 30 28 03 00       	call   0x5166c0
  4e3e90:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  4e3e96:	ba f4 01 00 00       	mov    edx,0x1f4
  4e3e9b:	6a 01                	push   0x1
  4e3e9d:	ff 35 f4 49 78 0a    	push   DWORD PTR ds:0xa7849f4
  4e3ea3:	56                   	push   esi
  4e3ea4:	68 18 01 00 00       	push   0x118
  4e3ea9:	68 f4 01 00 00       	push   0x1f4
  4e3eae:	e8 1d b1 02 00       	call   0x50efd0
  4e3eb3:	83 c4 34             	add    esp,0x34
  4e3eb6:	6a 00                	push   0x0
  4e3eb8:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3ebe:	ff d7                	call   edi
  4e3ec0:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4e3ec3:	83 c4 08             	add    esp,0x8
  4e3ec6:	33 cd                	xor    ecx,ebp
  4e3ec8:	5f                   	pop    edi
  4e3ec9:	5e                   	pop    esi
  4e3eca:	e8 df 61 0a 00       	call   0x58a0ae
  4e3ecf:	8b e5                	mov    esp,ebp
  4e3ed1:	5d                   	pop    ebp
  4e3ed2:	c3                   	ret
  4e3ed3:	cc                   	int3
  4e3ed4:	cc                   	int3
  4e3ed5:	cc                   	int3
  4e3ed6:	cc                   	int3
  4e3ed7:	cc                   	int3
  4e3ed8:	cc                   	int3
  4e3ed9:	cc                   	int3
  4e3eda:	cc                   	int3
  4e3edb:	cc                   	int3
  4e3edc:	cc                   	int3
  4e3edd:	cc                   	int3
  4e3ede:	cc                   	int3
  4e3edf:	cc                   	int3
  4e3ee0:	55                   	push   ebp
  4e3ee1:	8b ec                	mov    ebp,esp
  4e3ee3:	83 ec 2c             	sub    esp,0x2c
  4e3ee6:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4e3eeb:	33 c5                	xor    eax,ebp
  4e3eed:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4e3ef0:	a0 ad bc 5e 00       	mov    al,ds:0x5ebcad
  4e3ef5:	0f 28 05 c0 d7 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd7c0
  4e3efc:	53                   	push   ebx
  4e3efd:	56                   	push   esi
  4e3efe:	8b 35 80 fa 38 06    	mov    esi,DWORD PTR ds:0x638fa80
  4e3f04:	33 db                	xor    ebx,ebx
  4e3f06:	38 1d ac bc 5e 00    	cmp    BYTE PTR ds:0x5ebcac,bl
  4e3f0c:	57                   	push   edi
  4e3f0d:	ff 35 b0 37 39 06    	push   DWORD PTR ds:0x63937b0
  4e3f13:	8b 3d 88 c2 58 00    	mov    edi,DWORD PTR ds:0x58c288
  4e3f19:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3f1f:	88 45 d8             	mov    BYTE PTR [ebp-0x28],al
  4e3f22:	b8 02 00 00 00       	mov    eax,0x2
  4e3f27:	0f 44 d8             	cmove  ebx,eax
  4e3f2a:	0f 11 45 ec          	movups XMMWORD PTR [ebp-0x14],xmm0
  4e3f2e:	ff d7                	call   edi
  4e3f30:	8d 45 f8             	lea    eax,[ebp-0x8]
  4e3f33:	50                   	push   eax
  4e3f34:	8d 45 f4             	lea    eax,[ebp-0xc]
  4e3f37:	50                   	push   eax
  4e3f38:	6a 00                	push   0x0
  4e3f3a:	6a 00                	push   0x0
  4e3f3c:	56                   	push   esi
  4e3f3d:	ff 15 8c c1 58 00    	call   DWORD PTR ds:0x58c18c
  4e3f43:	83 c4 1c             	add    esp,0x1c
  4e3f46:	8d 45 ec             	lea    eax,[ebp-0x14]
  4e3f49:	50                   	push   eax
  4e3f4a:	6a 00                	push   0x0
  4e3f4c:	56                   	push   esi
  4e3f4d:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3f53:	ff 15 28 c2 58 00    	call   DWORD PTR ds:0x58c228
  4e3f59:	83 c4 10             	add    esp,0x10
  4e3f5c:	f6 c3 02             	test   bl,0x2
  4e3f5f:	74 2e                	je     0x4e3f8f
  4e3f61:	8b 45 f8             	mov    eax,DWORD PTR [ebp-0x8]
  4e3f64:	8b 4d f0             	mov    ecx,DWORD PTR [ebp-0x10]
  4e3f67:	48                   	dec    eax
  4e3f68:	8b 55 ec             	mov    edx,DWORD PTR [ebp-0x14]
  4e3f6b:	03 c1                	add    eax,ecx
  4e3f6d:	68 94 00 00 00       	push   0x94
  4e3f72:	6a 00                	push   0x0
  4e3f74:	6a 00                	push   0x0
  4e3f76:	6a 00                	push   0x0
  4e3f78:	50                   	push   eax
  4e3f79:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]
  4e3f7c:	48                   	dec    eax
  4e3f7d:	03 c2                	add    eax,edx
  4e3f7f:	50                   	push   eax
  4e3f80:	51                   	push   ecx
  4e3f81:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  4e3f87:	e8 c4 4e 02 00       	call   0x508e50
  4e3f8c:	83 c4 1c             	add    esp,0x1c
  4e3f8f:	6a 00                	push   0x0
  4e3f91:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3f97:	ff d7                	call   edi
  4e3f99:	ff 35 b0 37 39 06    	push   DWORD PTR ds:0x63937b0
  4e3f9f:	0f 28 05 d0 d7 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd7d0
  4e3fa6:	33 db                	xor    ebx,ebx
  4e3fa8:	38 5d d8             	cmp    BYTE PTR [ebp-0x28],bl
  4e3fab:	b8 02 00 00 00       	mov    eax,0x2
  4e3fb0:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3fb6:	8b 35 78 fa 38 06    	mov    esi,DWORD PTR ds:0x638fa78
  4e3fbc:	0f 44 d8             	cmove  ebx,eax
  4e3fbf:	0f 11 45 dc          	movups XMMWORD PTR [ebp-0x24],xmm0
  4e3fc3:	ff d7                	call   edi
  4e3fc5:	8d 45 e8             	lea    eax,[ebp-0x18]
  4e3fc8:	50                   	push   eax
  4e3fc9:	8d 45 e4             	lea    eax,[ebp-0x1c]
  4e3fcc:	50                   	push   eax
  4e3fcd:	6a 00                	push   0x0
  4e3fcf:	6a 00                	push   0x0
  4e3fd1:	56                   	push   esi
  4e3fd2:	ff 15 8c c1 58 00    	call   DWORD PTR ds:0x58c18c
  4e3fd8:	83 c4 24             	add    esp,0x24
  4e3fdb:	8d 45 dc             	lea    eax,[ebp-0x24]
  4e3fde:	50                   	push   eax
  4e3fdf:	6a 00                	push   0x0
  4e3fe1:	56                   	push   esi
  4e3fe2:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e3fe8:	ff 15 28 c2 58 00    	call   DWORD PTR ds:0x58c228
  4e3fee:	83 c4 10             	add    esp,0x10
  4e3ff1:	f6 c3 02             	test   bl,0x2
  4e3ff4:	74 2e                	je     0x4e4024
  4e3ff6:	8b 45 e8             	mov    eax,DWORD PTR [ebp-0x18]
  4e3ff9:	8b 4d e0             	mov    ecx,DWORD PTR [ebp-0x20]
  4e3ffc:	48                   	dec    eax
  4e3ffd:	8b 55 dc             	mov    edx,DWORD PTR [ebp-0x24]
  4e4000:	03 c1                	add    eax,ecx
  4e4002:	68 94 00 00 00       	push   0x94
  4e4007:	6a 00                	push   0x0
  4e4009:	6a 00                	push   0x0
  4e400b:	6a 00                	push   0x0
  4e400d:	50                   	push   eax
  4e400e:	8b 45 e4             	mov    eax,DWORD PTR [ebp-0x1c]
  4e4011:	48                   	dec    eax
  4e4012:	03 c2                	add    eax,edx
  4e4014:	50                   	push   eax
  4e4015:	51                   	push   ecx
  4e4016:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  4e401c:	e8 2f 4e 02 00       	call   0x508e50
  4e4021:	83 c4 1c             	add    esp,0x1c
  4e4024:	6a 00                	push   0x0
  4e4026:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e402c:	ff d7                	call   edi
  4e402e:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4e4031:	83 c4 08             	add    esp,0x8
  4e4034:	33 cd                	xor    ecx,ebp
  4e4036:	5f                   	pop    edi
  4e4037:	5e                   	pop    esi
  4e4038:	5b                   	pop    ebx
  4e4039:	e8 70 60 0a 00       	call   0x58a0ae
  4e403e:	8b e5                	mov    esp,ebp
  4e4040:	5d                   	pop    ebp
  4e4041:	c3                   	ret
; VA 004E5CD0..004E5E58; image base 00400000
  4e5cd0:	a1 98 87 5e 00       	mov    eax,ds:0x5e8798
  4e5cd5:	83 c4 0c             	add    esp,0xc
  4e5cd8:	8b 0d b0 37 39 06    	mov    ecx,DWORD PTR ds:0x63937b0
  4e5cde:	ba 4d 00 00 00       	mov    edx,0x4d
  4e5ce3:	a3 9c 4b 35 06       	mov    ds:0x6354b9c,eax
  4e5ce8:	c7 05 a0 4b 35 06 01 	mov    DWORD PTR ds:0x6354ba0,0x1
  4e5cef:	00 00 00 
  4e5cf2:	68 5c 6c 5a 00       	push   0x5a6c5c
  4e5cf7:	68 e6 00 00 00       	push   0xe6
  4e5cfc:	68 26 02 00 00       	push   0x226
  4e5d01:	e8 0a a0 fe ff       	call   0x4cfd10
  4e5d06:	8b 0d b0 37 39 06    	mov    ecx,DWORD PTR ds:0x63937b0
  4e5d0c:	83 c4 0c             	add    esp,0xc
  4e5d0f:	ba 41 00 00 00       	mov    edx,0x41
  4e5d14:	68 74 6c 5a 00       	push   0x5a6c74
  4e5d19:	68 f5 00 00 00       	push   0xf5
  4e5d1e:	68 26 02 00 00       	push   0x226
  4e5d23:	e8 e8 9f fe ff       	call   0x4cfd10
  4e5d28:	83 c4 0c             	add    esp,0xc
  4e5d2b:	85 db                	test   ebx,ebx
  4e5d2d:	75 08                	jne    0x4e5d37
  4e5d2f:	38 9d f5 fb ff ff    	cmp    BYTE PTR [ebp-0x40b],bl
  4e5d35:	74 22                	je     0x4e5d59
  4e5d37:	8b 0d b0 37 39 06    	mov    ecx,DWORD PTR ds:0x63937b0
  4e5d3d:	ba 51 00 00 00       	mov    edx,0x51
  4e5d42:	68 90 6c 5a 00       	push   0x5a6c90
  4e5d47:	68 04 01 00 00       	push   0x104
  4e5d4c:	68 26 02 00 00       	push   0x226
  4e5d51:	e8 ba 9f fe ff       	call   0x4cfd10
  4e5d56:	83 c4 0c             	add    esp,0xc
  4e5d59:	8b 0d b0 37 39 06    	mov    ecx,DWORD PTR ds:0x63937b0
  4e5d5f:	ba 43 00 00 00       	mov    edx,0x43
  4e5d64:	68 a8 6c 5a 00       	push   0x5a6ca8
  4e5d69:	68 c7 01 00 00       	push   0x1c7
  4e5d6e:	68 26 02 00 00       	push   0x226
  4e5d73:	e8 98 9f fe ff       	call   0x4cfd10
  4e5d78:	8b 0d b0 37 39 06    	mov    ecx,DWORD PTR ds:0x63937b0
  4e5d7e:	83 c4 0c             	add    esp,0xc
  4e5d81:	ba 25 04 00 00       	mov    edx,0x425
  4e5d86:	68 c4 6c 5a 00       	push   0x5a6cc4
  4e5d8b:	68 3a 02 00 00       	push   0x23a
  4e5d90:	68 26 02 00 00       	push   0x226
  4e5d95:	e8 76 9f fe ff       	call   0x4cfd10
  4e5d9a:	8b 0d b0 37 39 06    	mov    ecx,DWORD PTR ds:0x63937b0
  4e5da0:	83 c4 0c             	add    esp,0xc
  4e5da3:	ba 1b 00 00 00       	mov    edx,0x1b
  4e5da8:	68 c8 50 59 00       	push   0x5950c8
  4e5dad:	68 3a 02 00 00       	push   0x23a
  4e5db2:	6a 0a                	push   0xa
  4e5db4:	e8 57 9f fe ff       	call   0x4cfd10
  4e5db9:	8b 35 a4 87 5e 00    	mov    esi,DWORD PTR ds:0x5e87a4
  4e5dbf:	83 c4 0c             	add    esp,0xc
  4e5dc2:	8b 3d b0 37 39 06    	mov    edi,DWORD PTR ds:0x63937b0
  4e5dc8:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e5dce:	ff 15 6c c2 58 00    	call   DWORD PTR ds:0x58c26c
  4e5dd4:	83 c4 04             	add    esp,0x4
  4e5dd7:	8b d8                	mov    ebx,eax
  4e5dd9:	57                   	push   edi
  4e5dda:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e5de0:	8b 3d 88 c2 58 00    	mov    edi,DWORD PTR ds:0x58c288
  4e5de6:	ff d7                	call   edi
  4e5de8:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  4e5dee:	ba 0d 00 00 00       	mov    edx,0xd
  4e5df3:	6a 01                	push   0x1
  4e5df5:	56                   	push   esi
  4e5df6:	68 dc 6c 5a 00       	push   0x5a6cdc
  4e5dfb:	68 10 02 00 00       	push   0x210
  4e5e00:	e8 5b 84 02 00       	call   0x50e260
  4e5e05:	53                   	push   ebx
  4e5e06:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e5e0c:	ff d7                	call   edi
  4e5e0e:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e5e14:	ff 15 6c c2 58 00    	call   DWORD PTR ds:0x58c26c
  4e5e1a:	83 c4 24             	add    esp,0x24
  4e5e1d:	8b f0                	mov    esi,eax
  4e5e1f:	ff 35 b0 37 39 06    	push   DWORD PTR ds:0x63937b0
  4e5e25:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e5e2b:	ff d7                	call   edi
  4e5e2d:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  4e5e33:	ba 0a 00 00 00       	mov    edx,0xa
  4e5e38:	6a 01                	push   0x1
  4e5e3a:	ff 35 a4 87 5e 00    	push   DWORD PTR ds:0x5e87a4
  4e5e40:	68 18 6d 5a 00       	push   0x5a6d18
  4e5e45:	68 1c 02 00 00       	push   0x21c
  4e5e4a:	e8 d1 ee 02 00       	call   0x514d20
  4e5e4f:	56                   	push   esi
  4e5e50:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4e5e56:	ff d7                	call   edi
; VA 004CFD10..004CFF91; image base 00400000
  4cfd10:	55                   	push   ebp
  4cfd11:	8b ec                	mov    ebp,esp
  4cfd13:	81 ec 20 04 00 00    	sub    esp,0x420
  4cfd19:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4cfd1e:	33 c5                	xor    eax,ebp
  4cfd20:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  4cfd23:	53                   	push   ebx
  4cfd24:	8b 5d 10             	mov    ebx,DWORD PTR [ebp+0x10]
  4cfd27:	56                   	push   esi
  4cfd28:	57                   	push   edi
  4cfd29:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4cfd2f:	8b fa                	mov    edi,edx
  4cfd31:	89 8d ec fb ff ff    	mov    DWORD PTR [ebp-0x414],ecx
  4cfd37:	89 9d e8 fb ff ff    	mov    DWORD PTR [ebp-0x418],ebx
  4cfd3d:	33 f6                	xor    esi,esi
  4cfd3f:	ff 15 6c c2 58 00    	call   DWORD PTR ds:0x58c26c
  4cfd45:	8b 15 34 4a 35 06    	mov    edx,DWORD PTR ds:0x6354a34
  4cfd4b:	83 c4 04             	add    esp,0x4
  4cfd4e:	89 85 e4 fb ff ff    	mov    DWORD PTR [ebp-0x41c],eax
  4cfd54:	85 d2                	test   edx,edx
  4cfd56:	7e 39                	jle    0x4cfd91
  4cfd58:	a1 b0 49 35 06       	mov    eax,ds:0x63549b0
  4cfd5d:	b9 d8 ef 34 06       	mov    ecx,0x634efd8
  4cfd62:	39 39                	cmp    DWORD PTR [ecx],edi
  4cfd64:	75 20                	jne    0x4cfd86
  4cfd66:	be 01 00 00 00       	mov    esi,0x1
  4cfd6b:	85 c0                	test   eax,eax
  4cfd6d:	74 17                	je     0x4cfd86
  4cfd6f:	81 ff 23 04 00 00    	cmp    edi,0x423
  4cfd75:	c7 85 f0 fb ff ff 00 	mov    DWORD PTR [ebp-0x410],0x0
  4cfd7c:	00 00 00 
  4cfd7f:	0f 45 b5 f0 fb ff ff 	cmovne esi,DWORD PTR [ebp-0x410]
  4cfd86:	81 c1 e8 00 00 00    	add    ecx,0xe8
  4cfd8c:	83 ea 01             	sub    edx,0x1
  4cfd8f:	75 d1                	jne    0x4cfd62
  4cfd91:	8d 95 f4 fb ff ff    	lea    edx,[ebp-0x40c]
  4cfd97:	8b cb                	mov    ecx,ebx
  4cfd99:	2b d3                	sub    edx,ebx
  4cfd9b:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  4cfda0:	8a 01                	mov    al,BYTE PTR [ecx]
  4cfda2:	8d 49 01             	lea    ecx,[ecx+0x1]
  4cfda5:	88 44 0a ff          	mov    BYTE PTR [edx+ecx*1-0x1],al
  4cfda9:	84 c0                	test   al,al
  4cfdab:	75 f3                	jne    0x4cfda0
  4cfdad:	a1 30 4a 35 06       	mov    eax,ds:0x6354a30
  4cfdb2:	ff b5 ec fb ff ff    	push   DWORD PTR [ebp-0x414]
  4cfdb8:	a3 c4 ba 5b 06       	mov    ds:0x65bbac4,eax
  4cfdbd:	a1 9c 4a 35 06       	mov    eax,ds:0x6354a9c
  4cfdc2:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4cfdc8:	a3 54 ba 5b 06       	mov    ds:0x65bba54,eax
  4cfdcd:	ff 15 88 c2 58 00    	call   DWORD PTR ds:0x58c288
  4cfdd3:	a1 a0 4b 35 06       	mov    eax,ds:0x6354ba0
  4cfdd8:	8b 5d 0c             	mov    ebx,DWORD PTR [ebp+0xc]
  4cfddb:	83 c8 02             	or     eax,0x2
  4cfdde:	8b 55 08             	mov    edx,DWORD PTR [ebp+0x8]
  4cfde1:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  4cfde7:	50                   	push   eax
  4cfde8:	ff 35 9c 4b 35 06    	push   DWORD PTR ds:0x6354b9c
  4cfdee:	8d 85 f4 fb ff ff    	lea    eax,[ebp-0x40c]
  4cfdf4:	50                   	push   eax
  4cfdf5:	53                   	push   ebx
  4cfdf6:	e8 25 4f 04 00       	call   0x514d20
  4cfdfb:	83 c4 18             	add    esp,0x18
  4cfdfe:	c7 05 54 ba 5b 06 00 	mov    DWORD PTR ds:0x65bba54,0x0
  4cfe05:	00 00 00 
  4cfe08:	c7 05 c4 ba 5b 06 00 	mov    DWORD PTR ds:0x65bbac4,0x0
  4cfe0f:	00 00 00 
  4cfe12:	85 f6                	test   esi,esi
  4cfe14:	0f 85 51 01 00 00    	jne    0x4cff6b
  4cfe1a:	69 0d 34 4a 35 06 e8 	imul   ecx,DWORD PTR ds:0x6354a34,0xe8
  4cfe21:	00 00 00 
  4cfe24:	8b 55 08             	mov    edx,DWORD PTR [ebp+0x8]
  4cfe27:	a1 a8 4b 35 06       	mov    eax,ds:0x6354ba8
  4cfe2c:	83 c2 02             	add    edx,0x2
  4cfe2f:	8b 35 48 c3 58 00    	mov    esi,DWORD PTR ds:0x58c348
  4cfe35:	03 c2                	add    eax,edx
  4cfe37:	6a 2e                	push   0x2e
  4cfe39:	89 b9 d8 ef 34 06    	mov    DWORD PTR [ecx+0x634efd8],edi
  4cfe3f:	89 81 e0 ef 34 06    	mov    DWORD PTR [ecx+0x634efe0],eax
  4cfe45:	a1 ac 4b 35 06       	mov    eax,ds:0x6354bac
  4cfe4a:	40                   	inc    eax
  4cfe4b:	03 c3                	add    eax,ebx
  4cfe4d:	89 81 e4 ef 34 06    	mov    DWORD PTR [ecx+0x634efe4],eax
  4cfe53:	8d 85 f4 fb ff ff    	lea    eax,[ebp-0x40c]
  4cfe59:	50                   	push   eax
  4cfe5a:	c7 81 ec ef 34 06 12 	mov    DWORD PTR [ecx+0x634efec],0x12
  4cfe61:	00 00 00 
  4cfe64:	ff d6                	call   esi
  4cfe66:	83 c4 08             	add    esp,0x8
  4cfe69:	85 c0                	test   eax,eax
  4cfe6b:	74 1b                	je     0x4cfe88
  4cfe6d:	8d 8d f4 fb ff ff    	lea    ecx,[ebp-0x40c]
  4cfe73:	2b c1                	sub    eax,ecx
  4cfe75:	3d 00 04 00 00       	cmp    eax,0x400
  4cfe7a:	0f 83 11 01 00 00    	jae    0x4cff91
  4cfe80:	c6 84 05 f4 fb ff ff 	mov    BYTE PTR [ebp+eax*1-0x40c],0x0
  4cfe87:	00 
  4cfe88:	8d 8d f4 fb ff ff    	lea    ecx,[ebp-0x40c]
  4cfe8e:	8d 51 01             	lea    edx,[ecx+0x1]
  4cfe91:	8a 01                	mov    al,BYTE PTR [ecx]
  4cfe93:	41                   	inc    ecx
  4cfe94:	84 c0                	test   al,al
  4cfe96:	75 f9                	jne    0x4cfe91
  4cfe98:	8b bd e8 fb ff ff    	mov    edi,DWORD PTR [ebp-0x418]
  4cfe9e:	2b ca                	sub    ecx,edx
  4cfea0:	69 15 34 4a 35 06 e8 	imul   edx,DWORD PTR ds:0x6354a34,0xe8
  4cfea7:	00 00 00 
  4cfeaa:	8d 04 cd 0a 00 00 00 	lea    eax,[ecx*8+0xa]
  4cfeb1:	8b cf                	mov    ecx,edi
  4cfeb3:	8d 59 01             	lea    ebx,[ecx+0x1]
  4cfeb6:	89 82 f4 ef 34 06    	mov    DWORD PTR [edx+0x634eff4],eax
  4cfebc:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  4cfec0:	8a 01                	mov    al,BYTE PTR [ecx]
  4cfec2:	41                   	inc    ecx
  4cfec3:	84 c0                	test   al,al
  4cfec5:	75 f9                	jne    0x4cfec0
  4cfec7:	2b cb                	sub    ecx,ebx
  4cfec9:	6a 3c                	push   0x3c
  4cfecb:	8d 04 cd 0a 00 00 00 	lea    eax,[ecx*8+0xa]
  4cfed2:	89 82 e8 ef 34 06    	mov    DWORD PTR [edx+0x634efe8],eax
  4cfed8:	8d 85 f4 fb ff ff    	lea    eax,[ebp-0x40c]
  4cfede:	50                   	push   eax
  4cfedf:	ff d6                	call   esi
  4cfee1:	83 c4 08             	add    esp,0x8
  4cfee4:	85 c0                	test   eax,eax
  4cfee6:	75 12                	jne    0x4cfefa
  4cfee8:	8d 85 f4 fb ff ff    	lea    eax,[ebp-0x40c]
  4cfeee:	6a 5b                	push   0x5b
  4cfef0:	50                   	push   eax
  4cfef1:	ff d6                	call   esi
  4cfef3:	83 c4 08             	add    esp,0x8
  4cfef6:	85 c0                	test   eax,eax
  4cfef8:	74 18                	je     0x4cff12
  4cfefa:	69 05 34 4a 35 06 e8 	imul   eax,DWORD PTR ds:0x6354a34,0xe8
  4cff01:	00 00 00 
  4cff04:	83 80 e8 ef 34 06 f0 	add    DWORD PTR [eax+0x634efe8],0xfffffff0
  4cff0b:	83 80 f4 ef 34 06 f0 	add    DWORD PTR [eax+0x634eff4],0xfffffff0
  4cff12:	6a 2e                	push   0x2e
  4cff14:	57                   	push   edi
  4cff15:	ff d6                	call   esi
  4cff17:	8b 15 34 4a 35 06    	mov    edx,DWORD PTR ds:0x6354a34
  4cff1d:	83 c4 08             	add    esp,0x8
  4cff20:	69 ca e8 00 00 00    	imul   ecx,edx,0xe8
  4cff26:	81 c1 10 ef 34 06    	add    ecx,0x634ef10
  4cff2c:	85 c0                	test   eax,eax
  4cff2e:	75 20                	jne    0x4cff50
  4cff30:	f3 0f 7e 05 f4 4d 5a 	movq   xmm0,QWORD PTR ds:0x5a4df4
  4cff37:	00 
  4cff38:	66 a1 fc 4d 5a 00    	mov    ax,ds:0x5a4dfc
  4cff3e:	66 0f d6 01          	movq   QWORD PTR [ecx],xmm0
  4cff42:	66 89 41 08          	mov    WORD PTR [ecx+0x8],ax
  4cff46:	a0 fe 4d 5a 00       	mov    al,ds:0x5a4dfe
  4cff4b:	88 41 0a             	mov    BYTE PTR [ecx+0xa],al
  4cff4e:	eb 14                	jmp    0x4cff64
  4cff50:	f3 0f 7e 05 00 4e 5a 	movq   xmm0,QWORD PTR ds:0x5a4e00
  4cff57:	00 
  4cff58:	a0 08 4e 5a 00       	mov    al,ds:0x5a4e08
  4cff5d:	66 0f d6 01          	movq   QWORD PTR [ecx],xmm0
  4cff61:	88 41 08             	mov    BYTE PTR [ecx+0x8],al
  4cff64:	42                   	inc    edx
  4cff65:	89 15 34 4a 35 06    	mov    DWORD PTR ds:0x6354a34,edx
  4cff6b:	ff b5 e4 fb ff ff    	push   DWORD PTR [ebp-0x41c]
  4cff71:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4cff77:	ff 15 88 c2 58 00    	call   DWORD PTR ds:0x58c288
  4cff7d:	8b 4d f8             	mov    ecx,DWORD PTR [ebp-0x8]
  4cff80:	83 c4 08             	add    esp,0x8
  4cff83:	33 cd                	xor    ecx,ebp
  4cff85:	5f                   	pop    edi
  4cff86:	5e                   	pop    esi
  4cff87:	5b                   	pop    ebx
  4cff88:	e8 21 a1 0b 00       	call   0x58a0ae
  4cff8d:	8b e5                	mov    esp,ebp
  4cff8f:	5d                   	pop    ebp
  4cff90:	c3                   	ret
; VA 005625E4..00562632; image base 00400000
  5625e4:	8d b5 90 fb ff ff    	lea    esi,[ebp-0x470]
  5625ea:	8d 4e 01             	lea    ecx,[esi+0x1]
  5625ed:	0f 1f 00             	nop    DWORD PTR [eax]
  5625f0:	8a 06                	mov    al,BYTE PTR [esi]
  5625f2:	46                   	inc    esi
  5625f3:	84 c0                	test   al,al
  5625f5:	75 f9                	jne    0x5625f0
  5625f7:	8d 85 90 fb ff ff    	lea    eax,[ebp-0x470]
  5625fd:	2b f1                	sub    esi,ecx
  5625ff:	68 8c 50 59 00       	push   0x59508c
  562604:	50                   	push   eax
  562605:	ff 15 50 c3 58 00    	call   DWORD PTR ds:0x58c350
  56260b:	83 c4 08             	add    esp,0x8
  56260e:	f7 d8                	neg    eax
  562610:	1b c0                	sbb    eax,eax
  562612:	33 c9                	xor    ecx,ecx
  562614:	f7 d8                	neg    eax
  562616:	85 f6                	test   esi,esi
  562618:	0f 94 c1             	sete   cl
  56261b:	0b c1                	or     eax,ecx
  56261d:	75 71                	jne    0x562690
  56261f:	8d 95 90 fb ff ff    	lea    edx,[ebp-0x470]
  562625:	33 c9                	xor    ecx,ecx
  562627:	e8 d4 fc ff ff       	call   0x562300
  56262c:	be 01 00 00 00       	mov    esi,0x1
  562631:	eb 4b                	jmp    0x56267e
; VA 004D4280..004D42D0; image base 00400000
  4d4280:	55                   	push   ebp
  4d4281:	8b ec                	mov    ebp,esp
  4d4283:	51                   	push   ecx
  4d4284:	53                   	push   ebx
  4d4285:	8b 1d 64 c3 58 00    	mov    ebx,DWORD PTR ds:0x58c364
  4d428b:	8b c2                	mov    eax,edx
  4d428d:	56                   	push   esi
  4d428e:	57                   	push   edi
  4d428f:	8b 3d 50 c3 58 00    	mov    edi,DWORD PTR ds:0x58c350
  4d4295:	8b f1                	mov    esi,ecx
  4d4297:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4d429a:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  4d42a0:	ff 75 08             	push   DWORD PTR [ebp+0x8]
  4d42a3:	50                   	push   eax
  4d42a4:	56                   	push   esi
  4d42a5:	ff 15 c8 c4 58 00    	call   DWORD PTR ds:0x58c4c8
  4d42ab:	83 c4 0c             	add    esp,0xc
  4d42ae:	85 c0                	test   eax,eax
  4d42b0:	74 4b                	je     0x4d42fd
  4d42b2:	6a 0d                	push   0xd
  4d42b4:	56                   	push   esi
  4d42b5:	ff d3                	call   ebx
  4d42b7:	83 c4 08             	add    esp,0x8
  4d42ba:	85 c0                	test   eax,eax
  4d42bc:	74 03                	je     0x4d42c1
  4d42be:	c6 00 00             	mov    BYTE PTR [eax],0x0
  4d42c1:	6a 0a                	push   0xa
  4d42c3:	56                   	push   esi
  4d42c4:	ff d3                	call   ebx
  4d42c6:	83 c4 08             	add    esp,0x8
  4d42c9:	85 c0                	test   eax,eax
  4d42cb:	74 03                	je     0x4d42d0
  4d42cd:	c6 00 00             	mov    BYTE PTR [eax],0x0
; VA 00517BFC..00517C06; image base 00400000
  517bfc:	e8 1f b4 fc ff       	call   0x4e3020
  517c01:	e8 4a be fc ff       	call   0x4e3a50
