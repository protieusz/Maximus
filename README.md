# Maximus
Ieneko42c inspired keyboard with 38 keys and a 65mm Azoteq trackpad

Inspired by Ieneko42c by daraku__neko. Extra 2 mouse button keys are added as backup even though Azoteq can do gestures.
65mm trackpad makes a big difference compared to Ieneko42c 43mm trackpad. Operation is much smoother.
Keyboard is powered by Raspberry Pico RP2040, smd soldered to the pcb.  Diodes are also smd solder.

Print the pcb at your own risk. Tested but I am not responsible if it does not work on your end. No support will be provided. I will make a build guide soon.

QMK source for the trackpad is copied from the original designer of ieneko42c. Please refer to his QMK code for more accuracy. I just copied and pasted his code into my Maximus. https://github.com/darakuneko/keyboard/tree/main/qmk/ieneko42c

# NOTE: 
Azoteq trackpads that you buy may sometimes have QA issues i.e. the solder pads at the back will come right off during soldering and trackpad themselves might be a dud. So it is better to order 2 trackpads just to be sure from your supplier. QMK support for Azoteq is not official yet
so the QMK code that I use is copied from the ieneko42c. Currently there is a PR for Azoteq for QMK and hopefully the code gets merged soon. Before flashing the Maximus QMK code that has the trackpad code in it, test it out by flashing the Maximussimple QMK code first after you soldered your 
diodes and mcu unit. Don't attach your trackpad yet. This Maximussimple code test will ensure that your pcb is working. Your pcb print should have no issues unless there was a quality defect from favorite pcb printing factory. If after flashing the Maximus QMK code with the trackpad code and,
the trackpad function or the pcb itself stop working then it is most likely the code itself or the trackpad issue. PCB in general should have no issue. Since the trackpad is not officially supported so there will be some weird fanicky issues so users will have to test it out. Like I said before, 
there are risk involve building this Maximus but it will work eventually.

Full Production Pictures

![IMG_9873](https://github.com/protieusz/Maximus/assets/118025702/150c9ecf-06bd-4e93-9a97-fa1436af7d83)

![IMG_9872](https://github.com/protieusz/Maximus/assets/118025702/74bf31fa-2d37-4bdc-bc73-02cecf285dd1)

![1BD20A9A-02A6-4801-B49B-B6780D1312E6](https://github.com/protieusz/Maximus/assets/118025702/9d1430db-e5d1-4cee-a0ae-f13c6036c87f)

![664B217D-1D70-4054-9D0C-97979DA8313F](https://github.com/protieusz/Maximus/assets/118025702/eea7bb6d-c552-4fed-b868-e15ad618e43c)

![D36E33E3-472A-439D-B128-F0F0E7C0B3B7](https://github.com/protieusz/Maximus/assets/118025702/348b7394-d8a3-4aab-9c21-65053c15fe30)

![IMG_9854](https://github.com/protieusz/Maximus/assets/118025702/c5909ce0-4300-4276-8104-af13b412e836)

![IMG_9847](https://github.com/protieusz/Maximus/assets/118025702/43e3bd42-51f2-4e15-85ec-cb6cfb9cc8a2)

![IMG_9846](https://github.com/protieusz/Maximus/assets/118025702/f34c2e91-38d4-4297-bbe4-13143af8f9f8)

![IMG_9845](https://github.com/protieusz/Maximus/assets/118025702/12d1b323-eea2-4d20-8826-4537ad9841b6)

![IMG_9841](https://github.com/protieusz/Maximus/assets/118025702/4088b468-d975-4907-9481-253e504a26e2)

![IMG_9840](https://github.com/protieusz/Maximus/assets/118025702/6d0f2119-32e3-4176-a9a7-3409c0b3e1d9)

![IMG_9818](https://github.com/protieusz/Maximus/assets/118025702/1f437989-33f5-443a-a74b-defcbb0fa7bd)

![IMG_9799](https://github.com/protieusz/Maximus/assets/118025702/c37b0561-af0e-46d7-8cac-e2c8b2265725)

![IMG_9798](https://github.com/protieusz/Maximus/assets/118025702/3fbe6fbd-07f3-449c-a8bf-602e032efbeb)

![IMG_9807](https://github.com/protieusz/Maximus/assets/118025702/3023dd74-4ac8-4fa0-ba8c-c5e213535c58)


# License

<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/nc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg?ref=chooser-v1"></a></p>

You are free to:

Share — copy and redistribute the material in any medium or format

Adapt — remix, transform, and build upon the material

The licensor cannot revoke these freedoms as long as you follow the license terms.
Under the following terms:

Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.

NonCommercial — You may not use the material for commercial purposes.

ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.

No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.

Keyboards by ProtieusKeebs is licensed under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/?ref=chooser-v1)
