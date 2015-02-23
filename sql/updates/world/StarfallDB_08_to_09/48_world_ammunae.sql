REPLACE INTO `spell_script_names` (`spell_id`, `scriptname`) VALUES
(75725, 'spell_hoo_consume_life_energy'),
(75790, 'spell_hoo_rampant_growth'),
(89888, 'spell_hoo_rampant_growth'),
(73686, 'spell_hoo_fixate'),
(75774, 'spell_hoo_summon_bloodpetal_blossom'),
(75702, 'spell_hoo_noxious_spores'),
(89889, 'spell_hoo_noxious_spores');

REPLACE INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(39731, 0, 0x0, 0x1, '0'); -- Ammunae

-- Seedling Pods
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 16, `unit_flags`= 64, `unit_flags2`= 33556480, `flags_extra`= 0, `exp`= 3, `scriptname`= 'npc_hoo_seed_pod' WHERE `entry`= 51329;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 16, `unit_flags`= 33554496, `unit_flags2`= 2048, `flags_extra`= 128, `exp`= 3 WHERE `entry`= 40592;

-- Bloodpetal Sprout
UPDATE `creature_template` SET `difficulty_entry_1`= 48717 WHERE `entry`= 40630;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 16, `unit_flags`= 33816576, `unit_flags2`= 2048, `flags_extra`= 0, `exp`= 3, `scriptname`= 'npc_hoo_bloodpetal_sprout' WHERE `entry`= 40630;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 16, `unit_flags`= 33816576, `unit_flags2`= 2048, `flags_extra`= 0, `exp`= 3 WHERE `entry`= 48717;

-- Bloodpetal Blossom
UPDATE `creature_template` SET `difficulty_entry_1`= 48716 WHERE `entry`= 40622;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 16, `unit_flags`= 33816576, `unit_flags2`= 2048, `flags_extra`= 0, `exp`= 3, `scriptname`= 'npc_hoo_bloodpetal_blossom' WHERE `entry`= 40622;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 16, `unit_flags`= 33816576, `unit_flags2`= 2048, `flags_extra`= 0, `exp`= 3 WHERE `entry`= 48716;

-- Spore
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction`= 14, `unit_flags`= 0, `unit_flags2`= 2048, `flags_extra`= 0, `exp`= 3, `scriptname`= 'npc_hoo_spore' WHERE `entry`= 40585;

REPLACE INTO `spell_dbc` (`Id`,`Attributes`,`AttributesEx`,`AttributesEx2`,`AttributesEx3`,`AttributesEx4`,`AttributesEx5`,`AttributesEx6`,`AttributesEx7`,`AttributesEx8`,`AttributesEx9`,`AttributesEx10`,`CastingTimeIndex`,`DurationIndex`,`RangeIndex`,`SchoolMask`,`SpellAuraOptionsId`,`SpellCastingRequirementsId`,`SpellCategoriesId`,`SpellClassOptionsId`,`SpellEquippedItemsId`,`SpellLevelsId`,`SpellTargetRestrictionsId`,`SpellInterruptsId`,`Comment`) VALUES
(75791,256,0,4,262144,128,8,0,0,0,0,0,1,21,6,1,38,0,0,0,0,0,0,0,'Summon Bloodpetal Sprout'),
(75771,256,0,4,262144,128,8,0,0,0,0,0,1,21,6,1,38,0,0,0,0,0,0,0,'Bloodpetal Blossom');

DELETE FROM conditions WHERE SourceEntry IN (75702, 89889);
