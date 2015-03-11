-- Irestone Rumbler
SET @ENTRY := 42527;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,2000,2000,2000,2000,49,0,0,0,0,0,0,11,0,15,0,0.0,0.0,0.0,0.0,"OOC - Attack Creatures");

DELETE FROM `creature` WHERE `guid` = '745940';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(745940, 44350, 646, 1, 32768, 0, 1, 1189.74, 798.295, -66.7076, 2.10419, 300, 0, 0, 1, 0, 0, 0, 0, 0);

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746045) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746045; DELETE FROM creature_addon WHERE guid = 746045;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746019) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746019; DELETE FROM creature_addon WHERE guid = 746019;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746165) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746165; DELETE FROM creature_addon WHERE guid = 746165;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746221) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746221; DELETE FROM creature_addon WHERE guid = 746221;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746240) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746240; DELETE FROM creature_addon WHERE guid = 746240;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746064) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746064; DELETE FROM creature_addon WHERE guid = 746064;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746037) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746037; DELETE FROM creature_addon WHERE guid = 746037;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746220) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746220; DELETE FROM creature_addon WHERE guid = 746220;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746048) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746048; DELETE FROM creature_addon WHERE guid = 746048;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746015) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746015; DELETE FROM creature_addon WHERE guid = 746015;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746136) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746136; DELETE FROM creature_addon WHERE guid = 746136;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746060) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746060; DELETE FROM creature_addon WHERE guid = 746060;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746061) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746061; DELETE FROM creature_addon WHERE guid = 746061;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746132) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746132; DELETE FROM creature_addon WHERE guid = 746132;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746021) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746021; DELETE FROM creature_addon WHERE guid = 746021;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746007) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746007; DELETE FROM creature_addon WHERE guid = 746007;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746137) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746137; DELETE FROM creature_addon WHERE guid = 746137;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746098) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746098; DELETE FROM creature_addon WHERE guid = 746098;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746012) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746012; DELETE FROM creature_addon WHERE guid = 746012;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746004) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746004; DELETE FROM creature_addon WHERE guid = 746004;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 745999) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 745999; DELETE FROM creature_addon WHERE guid = 745999;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746212) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746212; DELETE FROM creature_addon WHERE guid = 746212;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 745986) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 745986; DELETE FROM creature_addon WHERE guid = 745986;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746232) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746232; DELETE FROM creature_addon WHERE guid = 746232;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746243) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746243; DELETE FROM creature_addon WHERE guid = 746243;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746035) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746035; DELETE FROM creature_addon WHERE guid = 746035;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746200) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746200; DELETE FROM creature_addon WHERE guid = 746200;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746038) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746038; DELETE FROM creature_addon WHERE guid = 746038;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746233) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746233; DELETE FROM creature_addon WHERE guid = 746233;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746191) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746191; DELETE FROM creature_addon WHERE guid = 746191;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746247) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746247; DELETE FROM creature_addon WHERE guid = 746247;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746141) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746141; DELETE FROM creature_addon WHERE guid = 746141;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746034) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746034; DELETE FROM creature_addon WHERE guid = 746034;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746245) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746245; DELETE FROM creature_addon WHERE guid = 746245;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746238) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746238; DELETE FROM creature_addon WHERE guid = 746238;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746142) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746142; DELETE FROM creature_addon WHERE guid = 746142;

-- Deletes creature Greater Fire Elemental (id: 44364, guid: 746020) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746020; DELETE FROM creature_addon WHERE guid = 746020;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746082) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746082; DELETE FROM creature_addon WHERE guid = 746082;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746184) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746184; DELETE FROM creature_addon WHERE guid = 746184;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746095) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746095; DELETE FROM creature_addon WHERE guid = 746095;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746160) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746160; DELETE FROM creature_addon WHERE guid = 746160;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746169) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746169; DELETE FROM creature_addon WHERE guid = 746169;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746056) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746056; DELETE FROM creature_addon WHERE guid = 746056;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746156) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746156; DELETE FROM creature_addon WHERE guid = 746156;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746170) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746170; DELETE FROM creature_addon WHERE guid = 746170;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746050) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746050; DELETE FROM creature_addon WHERE guid = 746050;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746175) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746175; DELETE FROM creature_addon WHERE guid = 746175;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746054) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746054; DELETE FROM creature_addon WHERE guid = 746054;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746176) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746176; DELETE FROM creature_addon WHERE guid = 746176;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746174) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746174; DELETE FROM creature_addon WHERE guid = 746174;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746229) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746229; DELETE FROM creature_addon WHERE guid = 746229;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746189) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746189; DELETE FROM creature_addon WHERE guid = 746189;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746172) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746172; DELETE FROM creature_addon WHERE guid = 746172;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746167) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746167; DELETE FROM creature_addon WHERE guid = 746167;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746051) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746051; DELETE FROM creature_addon WHERE guid = 746051;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746126) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746126; DELETE FROM creature_addon WHERE guid = 746126;

-- Deletes creature Irestone Rumbler (id: 42780, guid: 746158) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746158; DELETE FROM creature_addon WHERE guid = 746158;

-- Deletes creature Irestone Rumbler (id: 42780, guid: 745997) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 745997; DELETE FROM creature_addon WHERE guid = 745997;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746073) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746073; DELETE FROM creature_addon WHERE guid = 746073;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746028) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746028; DELETE FROM creature_addon WHERE guid = 746028;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746074) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746074; DELETE FROM creature_addon WHERE guid = 746074;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746055) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746055; DELETE FROM creature_addon WHERE guid = 746055;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746185) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746185; DELETE FROM creature_addon WHERE guid = 746185;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746106) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746106; DELETE FROM creature_addon WHERE guid = 746106;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746023) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746023; DELETE FROM creature_addon WHERE guid = 746023;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746244) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746244; DELETE FROM creature_addon WHERE guid = 746244;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746017) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746017; DELETE FROM creature_addon WHERE guid = 746017;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746047) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746047; DELETE FROM creature_addon WHERE guid = 746047;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746111) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746111; DELETE FROM creature_addon WHERE guid = 746111;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746133) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746133; DELETE FROM creature_addon WHERE guid = 746133;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746000) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746000; DELETE FROM creature_addon WHERE guid = 746000;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746210) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746210; DELETE FROM creature_addon WHERE guid = 746210;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746248) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746248; DELETE FROM creature_addon WHERE guid = 746248;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746040) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746040; DELETE FROM creature_addon WHERE guid = 746040;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746032) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746032; DELETE FROM creature_addon WHERE guid = 746032;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746123) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746123; DELETE FROM creature_addon WHERE guid = 746123;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746209) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746209; DELETE FROM creature_addon WHERE guid = 746209;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746027) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746027; DELETE FROM creature_addon WHERE guid = 746027;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746001) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746001; DELETE FROM creature_addon WHERE guid = 746001;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746003) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746003; DELETE FROM creature_addon WHERE guid = 746003;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746194) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746194; DELETE FROM creature_addon WHERE guid = 746194;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746033) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746033; DELETE FROM creature_addon WHERE guid = 746033;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746219) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746219; DELETE FROM creature_addon WHERE guid = 746219;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746077) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746077; DELETE FROM creature_addon WHERE guid = 746077;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746086) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746086; DELETE FROM creature_addon WHERE guid = 746086;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746076) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746076; DELETE FROM creature_addon WHERE guid = 746076;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746075) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746075; DELETE FROM creature_addon WHERE guid = 746075;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746130) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746130; DELETE FROM creature_addon WHERE guid = 746130;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746182) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746182; DELETE FROM creature_addon WHERE guid = 746182;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746251) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746251; DELETE FROM creature_addon WHERE guid = 746251;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746228) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746228; DELETE FROM creature_addon WHERE guid = 746228;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746166) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746166; DELETE FROM creature_addon WHERE guid = 746166;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746108) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746108; DELETE FROM creature_addon WHERE guid = 746108;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746164) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746164; DELETE FROM creature_addon WHERE guid = 746164;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746218) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746218; DELETE FROM creature_addon WHERE guid = 746218;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746065) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746065; DELETE FROM creature_addon WHERE guid = 746065;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746125) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746125; DELETE FROM creature_addon WHERE guid = 746125;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746211) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746211; DELETE FROM creature_addon WHERE guid = 746211;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746115) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746115; DELETE FROM creature_addon WHERE guid = 746115;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746107) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746107; DELETE FROM creature_addon WHERE guid = 746107;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746186) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746186; DELETE FROM creature_addon WHERE guid = 746186;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746180) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746180; DELETE FROM creature_addon WHERE guid = 746180;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746109) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746109; DELETE FROM creature_addon WHERE guid = 746109;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746044) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746044; DELETE FROM creature_addon WHERE guid = 746044;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746100) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746100; DELETE FROM creature_addon WHERE guid = 746100;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746196) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746196; DELETE FROM creature_addon WHERE guid = 746196;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746201) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746201; DELETE FROM creature_addon WHERE guid = 746201;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746250) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746250; DELETE FROM creature_addon WHERE guid = 746250;

-- Deletes creature Greater Fire Elemental (id: 44364, guid: 745859) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 745859; DELETE FROM creature_addon WHERE guid = 745859;

-- Deletes creature Greater Fire Elemental (id: 44364, guid: 745939) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 745939; DELETE FROM creature_addon WHERE guid = 745939;

-- Deletes creature Exhausted Fire Elemental (id: 44357, guid: 745942) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 745942; DELETE FROM creature_addon WHERE guid = 745942;

-- Deletes creature Irestone Rumbler (id: 42780, guid: 745944) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 745944; DELETE FROM creature_addon WHERE guid = 745944;

-- Deletes creature Irestone Rumbler (id: 42780, guid: 745943) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 745943; DELETE FROM creature_addon WHERE guid = 745943;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746242) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746242; DELETE FROM creature_addon WHERE guid = 746242;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746227) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746227; DELETE FROM creature_addon WHERE guid = 746227;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746246) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746246; DELETE FROM creature_addon WHERE guid = 746246;

-- Deletes creature Servant of Therazane (id: 42479, guid: 745982) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 745982; DELETE FROM creature_addon WHERE guid = 745982;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746139) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746139; DELETE FROM creature_addon WHERE guid = 746139;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746071) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746071; DELETE FROM creature_addon WHERE guid = 746071;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746069) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746069; DELETE FROM creature_addon WHERE guid = 746069;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746099) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746099; DELETE FROM creature_addon WHERE guid = 746099;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746140) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746140; DELETE FROM creature_addon WHERE guid = 746140;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746231) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746231; DELETE FROM creature_addon WHERE guid = 746231;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746149) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746149; DELETE FROM creature_addon WHERE guid = 746149;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746198) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746198; DELETE FROM creature_addon WHERE guid = 746198;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746124) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746124; DELETE FROM creature_addon WHERE guid = 746124;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746199) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746199; DELETE FROM creature_addon WHERE guid = 746199;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746112) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746112; DELETE FROM creature_addon WHERE guid = 746112;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746239) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746239; DELETE FROM creature_addon WHERE guid = 746239;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746070) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746070; DELETE FROM creature_addon WHERE guid = 746070;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746155) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746155; DELETE FROM creature_addon WHERE guid = 746155;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746043) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746043; DELETE FROM creature_addon WHERE guid = 746043;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746162) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746162; DELETE FROM creature_addon WHERE guid = 746162;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746230) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746230; DELETE FROM creature_addon WHERE guid = 746230;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746029) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746029; DELETE FROM creature_addon WHERE guid = 746029;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746241) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746241; DELETE FROM creature_addon WHERE guid = 746241;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746148) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746148; DELETE FROM creature_addon WHERE guid = 746148;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746016) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746016; DELETE FROM creature_addon WHERE guid = 746016;

-- Deletes creature Irestone Rumbler (id: 42527, guid: 746249) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746249; DELETE FROM creature_addon WHERE guid = 746249;

-- Deletes creature Greater Air Elemental (id: 44363, guid: 746011) in zone: 5042, area: 5291
DELETE FROM `creature` WHERE `guid` = 746011; DELETE FROM creature_addon WHERE guid = 746011;