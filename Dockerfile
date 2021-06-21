WORKDIR /usr/src/bot

COPY . .
RUN cmake .
RUN make -j4
CMD ./bot