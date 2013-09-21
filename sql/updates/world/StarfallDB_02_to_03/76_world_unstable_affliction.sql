-- Unstable Affliction spell bonus on dot and dispell
UPDATE `spell_bonus_data` SET `direct_bonus`='1.8', `dot_bonus`='-1', `ap_bonus`='-1', `ap_dot_bonus`='-1', `comments`='Warlock - Unstable Affliction Dispell' WHERE `entry`='31117';
UPDATE `spell_bonus_data` SET `direct_bonus`='-1', `dot_bonus`='0.2', `ap_bonus`='-1', `ap_dot_bonus`='-1' WHERE `entry`='30108';