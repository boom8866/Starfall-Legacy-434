DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (-23333, -23335) AND `spell_effect` IN (-46392, -46393);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(-23333, -46392, 0, 'Horde Flag -> Remove Focused Assault'),
(-23335, -46392, 0, 'Alliance Flag -> Remove Focused Assault'),
(-23333, -46393, 0, 'Horde Flag -> Remove Brutal Assault'),
(-23335, -46393, 0, 'Alliance Flag -> Remove Brutal Assault');