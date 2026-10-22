# Build the Ktor application inside a Linux container
FROM eclipse-temurin:21-jdk AS build

WORKDIR /app

COPY . .

RUN chmod +x gradlew
RUN ./gradlew installDist --no-daemon

# Run only the packaged application
FROM eclipse-temurin:21-jre

WORKDIR /app

COPY --from=build /app/build/install/ktor-server-6018/ ./

EXPOSE 8080

ENTRYPOINT ["./bin/ktor-server-6018"]