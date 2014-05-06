
-- Westfall Tornados Knockup aura
REPLACE INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(832, 2, '76080');

-- stranglethorn valley huge shattering water twist should kill players jumping down
REPLACE INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6015, 'at_the_shattering');
