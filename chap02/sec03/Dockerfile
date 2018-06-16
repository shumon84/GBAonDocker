FROM devkitpro/toolchain-base

WORKDIR /home

RUN dkp-pacman -Syyu --noconfirm gba-dev

ENV DEVKITARM /opt/devkitpro/devkitARM
ENV PATH $DEVKITARM/bin:/opt/devkitpro/tools/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
ENV SAMPLES /opt/devkitpro/examples/gba
ENV TEMPLATE $SAMPLES/template

CMD ["make"]