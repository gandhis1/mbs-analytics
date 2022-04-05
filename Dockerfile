FROM gcc:latest AS gcc-build
RUN useradd --create-home nonroot
USER nonroot
WORKDIR /home/nonroot/mbs-analytics/
COPY Makefile.config .
WORKDIR /home/nonroot/mbs-analytics/src/engine
COPY src/engine .
RUN make

FROM mcr.microsoft.com/dotnet/sdk:6.0-alpine3.15 AS dotnet-build
RUN adduser -D nonroot
USER nonroot
WORKDIR /home/nonroot/mbs-analytics/src/frontend
COPY src/frontend .
RUN dotnet restore -r alpine-x64
RUN dotnet publish --no-restore -c release -r alpine-x64 -f net6.0 /p:PublishTrimmed=true --self-contained true

FROM mcr.microsoft.com/dotnet/runtime-deps:6.0-alpine3.15
USER root
RUN adduser -D nonroot
USER nonroot
WORKDIR /home/nonroot/mbs-analytics/bin
COPY --from=gcc-build /home/nonroot/mbs-analytics/src/engine/bin/* .
COPY --from=dotnet-build /home/nonroot/mbs-analytics/src/frontend/bin/release/net6.0/alpine-x64/publish .

ENTRYPOINT [ "./frontend" ]
