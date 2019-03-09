xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 170;
 0.03239;0.69511;3.85692;,
 0.78289;1.00316;3.84954;,
 0.78538;1.00499;4.17953;,
 0.03489;0.69694;4.18690;,
 1.09572;1.75168;3.84303;,
 1.09821;1.75351;4.17301;,
 0.78764;2.50219;3.84119;,
 0.79013;2.50402;4.17117;,
 0.03911;2.81506;3.84510;,
 0.04161;2.81689;4.17509;,
 -0.71138;2.50701;3.85248;,
 -0.70889;2.50884;4.18246;,
 -1.02421;1.75849;3.85899;,
 -1.02172;1.76032;4.18898;,
 -0.71613;1.00797;3.86083;,
 -0.71364;1.00981;4.19082;,
 0.03239;0.69511;3.85692;,
 0.03489;0.69694;4.18690;,
 0.03575;1.75508;3.85101;,
 0.03575;1.75508;3.85101;,
 0.03575;1.75508;3.85101;,
 0.03575;1.75508;3.85101;,
 0.03575;1.75508;3.85101;,
 0.03575;1.75508;3.85101;,
 0.03575;1.75508;3.85101;,
 0.03575;1.75508;3.85101;,
 0.03825;1.75692;4.18100;,
 0.03825;1.75692;4.18100;,
 0.03825;1.75692;4.18100;,
 0.03825;1.75692;4.18100;,
 0.03825;1.75692;4.18100;,
 0.03825;1.75692;4.18100;,
 0.03825;1.75692;4.18100;,
 0.03825;1.75692;4.18100;,
 -0.00269;0.87782;-3.01828;,
 0.74697;1.18797;-3.01612;,
 0.74747;1.18445;-2.68614;,
 -0.00219;0.87430;-2.68830;,
 1.05775;1.93734;-3.00861;,
 1.05825;1.93382;-2.67863;,
 0.74759;2.68695;-3.00015;,
 0.74809;2.68344;-2.67017;,
 -0.00181;2.99770;-2.99570;,
 -0.00131;2.99418;-2.66572;,
 -0.75147;2.68755;-2.99786;,
 -0.75097;2.68403;-2.66788;,
 -1.06225;1.93818;-3.00537;,
 -1.06175;1.93466;-2.67539;,
 -0.75209;1.18856;-3.01383;,
 -0.75159;1.18505;-2.68385;,
 -0.00269;0.87782;-3.01828;,
 -0.00219;0.87430;-2.68830;,
 -0.00225;1.93776;-3.00699;,
 -0.00225;1.93776;-3.00699;,
 -0.00225;1.93776;-3.00699;,
 -0.00225;1.93776;-3.00699;,
 -0.00225;1.93776;-3.00699;,
 -0.00225;1.93776;-3.00699;,
 -0.00225;1.93776;-3.00699;,
 -0.00225;1.93776;-3.00699;,
 -0.00175;1.93424;-2.67701;,
 -0.00175;1.93424;-2.67701;,
 -0.00175;1.93424;-2.67701;,
 -0.00175;1.93424;-2.67701;,
 -0.00175;1.93424;-2.67701;,
 -0.00175;1.93424;-2.67701;,
 -0.00175;1.93424;-2.67701;,
 -0.00175;1.93424;-2.67701;,
 -0.00200;1.23152;-3.16434;,
 0.50005;1.43944;-3.16071;,
 0.50005;1.42862;-2.54081;,
 -0.00200;1.22070;-2.54444;,
 0.70800;1.94141;-3.15195;,
 0.70800;1.93059;-2.53205;,
 0.50005;2.44338;-3.14319;,
 0.50005;2.43256;-2.52329;,
 -0.00200;2.65130;-3.13956;,
 -0.00200;2.64048;-2.51966;,
 -0.50405;2.44338;-3.14319;,
 -0.50405;2.43256;-2.52329;,
 -0.71200;1.94141;-3.15195;,
 -0.71200;1.93059;-2.53205;,
 -0.50405;1.43944;-3.16071;,
 -0.50405;1.42862;-2.54081;,
 -0.00200;1.23152;-3.16434;,
 -0.00200;1.22070;-2.54444;,
 -0.00200;1.94141;-3.15195;,
 -0.00200;1.94141;-3.15195;,
 -0.00200;1.94141;-3.15195;,
 -0.00200;1.94141;-3.15195;,
 -0.00200;1.94141;-3.15195;,
 -0.00200;1.94141;-3.15195;,
 -0.00200;1.94141;-3.15195;,
 -0.00200;1.94141;-3.15195;,
 -0.00200;1.93059;-2.53205;,
 -0.00200;1.93059;-2.53205;,
 -0.00200;1.93059;-2.53205;,
 -0.00200;1.93059;-2.53205;,
 -0.00200;1.93059;-2.53205;,
 -0.00200;1.93059;-2.53205;,
 -0.00200;1.93059;-2.53205;,
 -0.00200;1.93059;-2.53205;,
 -0.03665;2.48416;4.33562;,
 0.46578;2.27713;4.33466;,
 0.46446;2.27680;3.71467;,
 -0.03797;2.48383;3.71562;,
 0.67466;1.77547;4.33449;,
 0.67334;1.77514;3.71449;,
 0.46763;1.27304;4.33520;,
 0.46631;1.27271;3.71520;,
 -0.03403;1.06417;4.33637;,
 -0.03535;1.06384;3.71638;,
 -0.53646;1.27120;4.33733;,
 -0.53778;1.27087;3.71734;,
 -0.74534;1.77286;4.33751;,
 -0.74666;1.77253;3.71751;,
 -0.53831;2.27529;4.33680;,
 -0.53963;2.27496;3.71680;,
 -0.03665;2.48416;4.33562;,
 -0.03797;2.48383;3.71562;,
 -0.03534;1.77417;4.33600;,
 -0.03534;1.77417;4.33600;,
 -0.03534;1.77417;4.33600;,
 -0.03534;1.77417;4.33600;,
 -0.03534;1.77417;4.33600;,
 -0.03534;1.77417;4.33600;,
 -0.03534;1.77417;4.33600;,
 -0.03534;1.77417;4.33600;,
 -0.03666;1.77383;3.71600;,
 -0.03666;1.77383;3.71600;,
 -0.03666;1.77383;3.71600;,
 -0.03666;1.77383;3.71600;,
 -0.03666;1.77383;3.71600;,
 -0.03666;1.77383;3.71600;,
 -0.03666;1.77383;3.71600;,
 -0.03666;1.77383;3.71600;,
 -0.00465;1.94435;-3.16451;,
 0.08045;1.97890;-3.16480;,
 0.16201;1.83625;3.66323;,
 0.07691;1.80171;3.66352;,
 0.11621;2.06348;-3.16346;,
 0.19777;1.92084;3.66456;,
 0.08168;2.14856;-3.16127;,
 0.16324;2.00591;3.66675;,
 -0.00291;2.18429;-3.15951;,
 0.07865;2.04165;3.66851;,
 -0.08801;2.14975;-3.15922;,
 -0.00645;2.00710;3.66880;,
 -0.12377;2.06516;-3.16056;,
 -0.04221;1.92252;3.66746;,
 -0.08924;1.98009;-3.16275;,
 -0.00768;1.83744;3.66528;,
 -0.00465;1.94435;-3.16451;,
 0.07691;1.80171;3.66352;,
 0.00000;2.00000;-3.00000;,
 0.00000;2.00000;-3.00000;,
 0.00000;2.00000;-3.00000;,
 0.00000;2.00000;-3.00000;,
 0.00000;2.00000;-3.00000;,
 0.00000;2.00000;-3.00000;,
 0.00000;2.00000;-3.00000;,
 0.00000;2.00000;-3.00000;,
 0.07778;1.92168;3.66602;,
 0.07778;1.92168;3.66602;,
 0.07778;1.92168;3.66602;,
 0.07778;1.92168;3.66602;,
 0.07778;1.92168;3.66602;,
 0.07778;1.92168;3.66602;,
 0.07778;1.92168;3.66602;,
 0.07778;1.92168;3.66602;;
 
 120;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 3;52,35,34;,
 3;53,38,35;,
 3;54,40,38;,
 3;55,42,40;,
 3;56,44,42;,
 3;57,46,44;,
 3;58,48,46;,
 3;59,50,48;,
 3;60,37,36;,
 3;61,36,39;,
 3;62,39,41;,
 3;63,41,43;,
 3;64,43,45;,
 3;65,45,47;,
 3;66,47,49;,
 3;67,49,51;,
 4;68,69,70,71;,
 4;69,72,73,70;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 3;86,69,68;,
 3;87,72,69;,
 3;88,74,72;,
 3;89,76,74;,
 3;90,78,76;,
 3;91,80,78;,
 3;92,82,80;,
 3;93,84,82;,
 3;94,71,70;,
 3;95,70,73;,
 3;96,73,75;,
 3;97,75,77;,
 3;98,77,79;,
 3;99,79,81;,
 3;100,81,83;,
 3;101,83,85;,
 4;102,103,104,105;,
 4;103,106,107,104;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 3;120,103,102;,
 3;121,106,103;,
 3;122,108,106;,
 3;123,110,108;,
 3;124,112,110;,
 3;125,114,112;,
 3;126,116,114;,
 3;127,118,116;,
 3;128,105,104;,
 3;129,104,107;,
 3;130,107,109;,
 3;131,109,111;,
 3;132,111,113;,
 3;133,113,115;,
 3;134,115,117;,
 3;135,117,119;,
 4;136,137,138,139;,
 4;137,140,141,138;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 3;154,137,136;,
 3;155,140,137;,
 3;156,142,140;,
 3;157,144,142;,
 3;158,146,144;,
 3;159,148,146;,
 3;160,150,148;,
 3;161,152,150;,
 3;162,139,138;,
 3;163,138,141;,
 3;164,141,143;,
 3;165,143,145;,
 3;166,145,147;,
 3;167,147,149;,
 3;168,149,151;,
 3;169,151,153;;
 
 MeshMaterialList {
  3;
  120;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.034400;0.034400;0.034400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.649412;0.649412;0.649412;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.276000;0.263200;0.272800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  129;
  -0.007548;-0.005549;-0.999956;,
  -0.003170;-0.999979;0.005577;,
  0.704841;-0.709364;-0.001388;,
  0.999967;-0.003210;-0.007528;,
  0.709325;0.704821;-0.009264;,
  0.003173;0.999979;-0.005569;,
  -0.704841;0.709364;0.001388;,
  -0.999967;0.003211;0.007531;,
  -0.709323;-0.704822;0.009275;,
  0.007550;0.005550;0.999956;,
  -0.001524;0.010653;-0.999942;,
  -0.000414;-0.999943;-0.010659;,
  0.706812;-0.707349;-0.008617;,
  0.999999;-0.000397;-0.001523;,
  0.707397;0.706787;0.006457;,
  0.000414;0.999943;0.010658;,
  -0.706812;0.707349;0.008617;,
  -0.999999;0.000397;0.001523;,
  -0.707397;-0.706787;-0.006457;,
  0.001524;-0.010653;0.999942;,
  0.000000;0.017450;-0.999848;,
  0.000000;-0.999848;-0.017452;,
  0.707107;-0.706999;-0.012340;,
  1.000000;0.000000;0.000000;,
  0.707107;0.706999;0.012340;,
  0.000000;0.999848;0.017452;,
  -0.707107;0.706999;0.012340;,
  -1.000000;0.000000;0.000000;,
  -0.707107;-0.706999;-0.012340;,
  0.000000;-0.017450;0.999848;,
  0.002126;0.000534;0.999998;,
  -0.001836;0.999998;-0.000528;,
  0.705799;0.708409;-0.001880;,
  0.999996;0.001843;-0.002130;,
  0.708402;-0.705809;-0.001133;,
  0.001836;-0.999998;0.000528;,
  -0.705799;-0.708409;0.001880;,
  -0.999996;-0.001843;0.002130;,
  -0.708402;0.705809;0.001133;,
  -0.002125;-0.000538;-0.999998;,
  -0.753417;0.379199;-0.537188;,
  -0.007261;-0.999757;-0.020799;,
  0.701906;-0.711890;-0.023256;,
  0.999902;-0.006994;-0.012090;,
  0.712163;0.701987;0.006159;,
  0.007261;0.999757;0.020799;,
  -0.701906;0.711890;0.023256;,
  -0.999902;0.006994;0.012090;,
  -0.712163;-0.701987;-0.006159;,
  0.011933;-0.020852;0.999711;,
  -0.007550;-0.005547;-0.999956;,
  -0.007549;-0.005551;-0.999956;,
  -0.007546;-0.005546;-0.999956;,
  -0.007545;-0.005550;-0.999956;,
  -0.007549;-0.005552;-0.999956;,
  -0.007550;-0.005547;-0.999956;,
  -0.007546;-0.005546;-0.999956;,
  -0.007545;-0.005550;-0.999956;,
  0.007549;0.005542;0.999956;,
  0.007550;0.005547;0.999956;,
  0.007556;0.005553;0.999956;,
  0.007557;0.005552;0.999956;,
  0.007549;0.005552;0.999956;,
  0.007543;0.005554;0.999956;,
  0.007546;0.005553;0.999956;,
  0.007549;0.005545;0.999956;,
  -0.001525;0.010652;-0.999942;,
  -0.001523;0.010652;-0.999942;,
  -0.001524;0.010654;-0.999942;,
  -0.001522;0.010653;-0.999942;,
  -0.001523;0.010652;-0.999942;,
  -0.001525;0.010652;-0.999942;,
  -0.001524;0.010654;-0.999942;,
  -0.001523;0.010653;-0.999942;,
  0.001523;-0.010652;0.999942;,
  0.001525;-0.010652;0.999942;,
  0.001524;-0.010654;0.999942;,
  0.001523;-0.010653;0.999942;,
  0.001523;-0.010652;0.999942;,
  0.001525;-0.010652;0.999942;,
  0.001524;-0.010654;0.999942;,
  0.001522;-0.010653;0.999942;,
  0.000001;0.017450;-0.999848;,
  0.000000;0.017451;-0.999848;,
  0.000000;0.017449;-0.999848;,
  -0.000001;0.017450;-0.999848;,
  0.000000;0.017451;-0.999848;,
  0.000001;0.017450;-0.999848;,
  -0.000001;0.017450;-0.999848;,
  0.000000;-0.017451;0.999848;,
  -0.000001;-0.017450;0.999848;,
  0.000000;-0.017449;0.999848;,
  0.000001;-0.017450;0.999848;,
  0.000000;-0.017451;0.999848;,
  -0.000001;-0.017450;0.999848;,
  0.000001;-0.017450;0.999848;,
  0.002130;0.000543;0.999998;,
  0.002130;0.000539;0.999998;,
  0.002126;0.000542;0.999998;,
  0.002120;0.000531;0.999998;,
  0.002120;0.000525;0.999998;,
  0.002126;0.000526;0.999998;,
  0.002126;0.000532;0.999998;,
  0.002127;0.000538;0.999998;,
  -0.002120;-0.000539;-0.999998;,
  -0.002119;-0.000533;-0.999998;,
  -0.002126;-0.000532;-0.999998;,
  -0.002127;-0.000538;-0.999998;,
  -0.002130;-0.000539;-0.999998;,
  -0.002129;-0.000543;-0.999998;,
  -0.002126;-0.000542;-0.999998;,
  -0.002127;-0.000538;-0.999998;,
  -0.633877;0.665196;-0.394606;,
  0.002146;0.947248;-0.320493;,
  -0.821613;0.039814;-0.568654;,
  -0.527066;-0.475106;-0.704610;,
  0.248557;-0.572322;-0.781452;,
  -0.014461;-0.654505;-0.755919;,
  0.497135;-0.477857;-0.724230;,
  0.797292;0.028825;-0.602906;,
  0.627626;0.652912;-0.424018;,
  0.011931;-0.020917;0.999710;,
  0.011957;-0.020857;0.999711;,
  0.012017;-0.020827;0.999711;,
  0.012007;-0.020848;0.999711;,
  0.011931;-0.020838;0.999712;,
  0.011859;-0.020844;0.999712;,
  0.011852;-0.020826;0.999713;,
  0.011909;-0.020860;0.999712;;
  120;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,50,51;,
  3;0,52,50;,
  3;0,53,52;,
  3;0,54,53;,
  3;0,55,54;,
  3;0,56,55;,
  3;0,57,56;,
  3;0,51,57;,
  3;9,58,59;,
  3;9,59,60;,
  3;9,60,61;,
  3;9,61,62;,
  3;9,62,63;,
  3;9,63,64;,
  3;9,64,65;,
  3;9,65,58;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,11,11,18;,
  3;10,66,67;,
  3;10,68,66;,
  3;10,69,68;,
  3;10,70,69;,
  3;10,71,70;,
  3;10,72,71;,
  3;10,73,72;,
  3;10,67,73;,
  3;19,74,75;,
  3;19,75,76;,
  3;19,76,77;,
  3;19,77,78;,
  3;19,78,79;,
  3;19,79,80;,
  3;19,80,81;,
  3;19,81,74;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,21,21,28;,
  3;20,82,83;,
  3;20,84,82;,
  3;20,85,84;,
  3;20,86,85;,
  3;20,87,86;,
  3;20,84,87;,
  3;20,88,84;,
  3;20,83,88;,
  3;29,89,90;,
  3;29,90,91;,
  3;29,91,92;,
  3;29,92,93;,
  3;29,93,94;,
  3;29,94,91;,
  3;29,91,95;,
  3;29,95,89;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,31,31,38;,
  3;30,96,97;,
  3;30,98,96;,
  3;30,99,98;,
  3;30,100,99;,
  3;30,101,100;,
  3;30,102,101;,
  3;30,103,102;,
  3;30,97,103;,
  3;39,104,105;,
  3;39,105,106;,
  3;39,106,107;,
  3;39,107,108;,
  3;39,108,109;,
  3;39,109,110;,
  3;39,110,111;,
  3;39,111,104;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,41,41,48;,
  3;40,112,113;,
  3;40,114,112;,
  3;40,115,114;,
  3;116,117,115;,
  3;116,118,117;,
  3;116,119,118;,
  3;120,120,119;,
  3;120,113,120;,
  3;49,121,122;,
  3;49,122,123;,
  3;49,123,124;,
  3;49,124,125;,
  3;49,125,126;,
  3;49,126,127;,
  3;49,127,128;,
  3;49,128,121;;
 }
 MeshTextureCoords {
  170;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
