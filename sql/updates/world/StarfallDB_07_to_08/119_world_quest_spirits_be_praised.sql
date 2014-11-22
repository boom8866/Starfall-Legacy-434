UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=2 WHERE `Id`=25189;

-- Deletes creature Grandmatron Tekla (id: 39325, guid: 141324) in zone: 14, area: 4981
DELETE FROM `creature` WHERE `guid` = 141324; DELETE FROM creature_addon WHERE guid = 141324;