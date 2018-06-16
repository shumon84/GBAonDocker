FROM devkitpro/toolchain-base

WORKDIR /home

RUN dkp-pacman -Syyu --noconfirm gba-dev

ENV DEVKITARM ${DEVKITPRO}/devkitARM
ENV PATH ${DEVKITARM}/bin:${PATH}
ENV SAMPLES ${DEVKITPRO}/examples/gba
ENV TEMPLATE ${SAMPLES}/template

CMD ["make"]