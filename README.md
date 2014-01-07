# PSTE shazam - Music matching #


## Introduction ##
This is a student project (at ECE Paris), for the year 2013-2014. I am part of a
6 students group.

I choose to use the C programming langage, because this is the only one I know
and I am too lazy to learn a new programming langage.


## Hacking and exploring - Code structure ##

### Make_hash ###
Prog to load a .wav (mp3 not suported yet), perform a Fourier Transform and encode
the highest frequencies to a hash and save them in a .txt file.
- main.c : no comment
- ft_utils.c : error checking for functions like malloc
- ft_init.c : load the music, malloc the fft struct and perform the fft + free functions
- ft_getHash.c : retrieve the highest intensities for each given time
- ft_time_analyse : stats about time for stats

### Match ###
Prog to compare hash files mades with the above prog, and output a sumary of the number
of matchs found for each file.
- main.c : no comment
- ft_loadHash.c : load database
- ft_compare : compare and get the number of matching hash


## Usefull documents ##
- A post from redcode : very usefull, altough it used java http://www.redcode.nl/blog/2010/06/creating-shazam-in-java/
- Fmod ex : not really working
- SDL : for all graphic rendering http://www.libsdl.org/
- Fftw : C librairy for Fourier transforms http://www.fftw.org/


## Changes - History ##
- sept - oct : googling ... found a post on redcode about a Java coded shazam
- nov : start coding : tryed the Fourier Transform with Fmod ex and a graphic rendering
  (spectrogram) with SDL. Not really working, moreover spectrograms are more funny than uselfull. 
- dec : found the fftw lib, the paramount for Fourier transform. It own a large amount of FFT functions,
  I tryed one randomly, it provide good results for a beginning but need some adjustements.
- jan : finish Make_hash code and coding Match


## Credits and license ##
The code is open source (for now, but if my group decide to keep it for us this repo
would be removed), but please indicate the author if you use it for a project.

